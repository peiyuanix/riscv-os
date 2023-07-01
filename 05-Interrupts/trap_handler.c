#include "riscv_cpu.h"
#include "uart.h"
#include "timer.h"

cpu_t trap_cpu;

void trap_handler()
{
  uart_printf("[trap_handler] mcause: 0x%x, current ticks: %d\n", csrr_mcause(), mtime());
  set_timeout(10000000);
}