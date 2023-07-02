#include "riscv_cpu.h"
#include "uart.h"
#include "timer.h"
#include "interrupts.h"

struct cpu trap_cpu;

void trap_handler()
{
  u64 mcause = csrr_mcause();
  switch (mcause)
  {
  case MCAUSE_INTR_M_TIMER:
  {
    uart_printf("[Trap - M-mode Timer] mcause: 0x%lx, current ticks: %d\n", mcause, mtime());
    set_timeout(10000000);
    break;
  }

  default:
  {
    uart_printf("[Trap - Default] mcause: 0x%lX\n", mcause);
    break;
  }
  }
}