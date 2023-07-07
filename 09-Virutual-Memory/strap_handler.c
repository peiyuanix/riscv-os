#include "riscv_cpu.h"
#include "uart.h"
#include "timer.h"
#include "proc.h"
#include "riscv_priv.h"

struct cpu strap_cpu;
u8 strap_stack[1 << 20];
void *strap_stack_top = &strap_stack[sizeof(strap_stack) - 1];

void strap_handler()
{
  u64 scause = csrr_scause();
  switch (scause)
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
        strap_cpu = proc_list[0].cpu;
        uart_printf("[STrap - Timer] Scheduler Init. Ticks: %ld\n", active_pid, scause, 0);
      }

      // save cpu state for the active process
      proc_list[active_pid].cpu = strap_cpu;
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
          uart_printf("[STrap - Timer] Scheduler(Ticks = %ld): (PID = %d, PC = 0x%lx) => (PID = %d, PC = 0x%lx)\n", 0, active_pid, strap_cpu.pc, proc->pid, proc->cpu.pc);
          strap_cpu = proc->cpu;
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
    uart_printf("[STrap - Exter] active_pid: %d, mcause: 0x%lX, current ticks: %d\n", active_pid, scause, 0);
    break;
  }

  case MCAUSE_INNER_M_ILLEAGEL_INSTRUCTION:
  {
    uart_printf("[STrap - Illeagel Instruction] active_pid: %d, mcause: 0x%lX, mepc: %lx\n", active_pid, scause, csrr_mepc());
    break;
  }

  default:
  {
    uart_printf("[STrap - Default] active_pid: %d, mcause: 0x%lX, current ticks: %d\n", active_pid, scause, 0);
    while (1);
    break;
  }
  }
}