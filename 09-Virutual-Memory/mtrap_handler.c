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
    // notify S-mode that M-mode timer timeout
    csrs_mip(MIE_STIE);
    csrs_mie(MIE_STIE);
    set_timeout(1000000);
    break;
  }

  case MCAUSE_INTR_M_EXTER:
  {
    uart_printf("[MTrap -  Exter] active_pid: %d, mcause: 0x%lX, current ticks: %d\n", active_pid, mcause, mtime());
    break;
  }

  case MCAUSE_INNER_ILLEAGEL_INSTRUCTION:
  {
    uart_printf("[MTrap -  Illeagel Instruction] active_pid: %d, mcause: 0x%lX, mepc: %lx\n", active_pid, mcause, csrr_mepc());
    break;
  }

  default:
  {
    uart_printf("[MTrap - Default] active_pid: %d, mcause: 0x%lX, current ticks: %d\n", active_pid, mcause, mtime());
    while (1)
      ;
    break;
  }
  }
}