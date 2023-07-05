#include "riscv_cpu.h"
#include "uart.h"
#include "timer.h"
#include "proc.h"
#include "riscv_priv.h"

struct cpu mtrap_cpu;
u8 mtrap_stack[1 << 20];
void *mtrap_stack_top = &mtrap_stack[sizeof(mtrap_stack) - 1];

void mtrap_handler()
{
  u64 mcause = csrr_mcause();
  switch (mcause)
  {
  case MCAUSE_INTR_M_TIMER:
  {
    // there exists runnable processes
    if (proc_list[0].state != PROC_STATE_NONE)
    {
      // assume proc-0 is the active process if there is no active process
      if (active_pid < 0)
      {
        active_pid = 0;
        mtrap_cpu = proc_list[0].cpu;
        uart_printf("[MTrap -  Timer] Scheduler Init. Ticks: %ld\n", active_pid, mcause, mtime());
      }

      // save cpu state for the active process
      proc_list[active_pid].cpu = mtrap_cpu;
      // suspend the active process
      proc_list[active_pid].state = PROC_STATE_READY;

      // iterate the processes from the next process, ending with the active process
      for (int ring_index = 1; ring_index <= PROC_TOTAL_COUNT; ring_index++)
      {
        int real_index = (active_pid + ring_index) % PROC_TOTAL_COUNT;
        struct proc *proc = &proc_list[real_index];
        // run this process if it is ready
        if (proc->state == PROC_STATE_READY)
        {
          uart_printf("[MTrap -  Timer] Scheduler(Ticks = %ld): (PID = %d, PC = 0x%lx) => (PID = %d, PC = 0x%lx)\n", mtime(), active_pid, mtrap_cpu.pc, proc->pid, proc->cpu.pc);
          mtrap_cpu = proc->cpu;
          active_pid = proc->pid;
          break;
        }
      }
    }
    set_timeout(10000000);
    break;
  }

  case MCAUSE_INTR_M_EXTER:
  {
    uart_printf("[MTrap -  Exter] active_pid: %d, mcause: 0x%lX, current ticks: %d\n", active_pid, mcause, mtime());
    break;
  }

  case MCAUSE_INNER_M_ILLEAGEL_INSTRUCTION:
  {
    uart_printf("[MTrap -  Illeagel Instruction] active_pid: %d, mcause: 0x%lX, mepc: %lx\n", active_pid, mcause, csrr_mepc());
    break;
  }

  default:
  {
    uart_printf("[MTrap - Default] active_pid: %d, mcause: 0x%lX, current ticks: %d\n", active_pid, mcause, mtime());
    break;
  }
  }
}