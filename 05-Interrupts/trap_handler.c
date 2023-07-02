#include "riscv_cpu.h"
#include "uart.h"
#include "timer.h"

cpu_t trap_cpu;

void trap_handler()
{
  u64 mcause = csrr_mcause();
  uart_printf("[trap_handler] mcause: 0x%lX, current ticks: %d\n", mcause, mtime());
  set_timeout(10000000);
}