#include "riscv_cpu.h"
#include "uart.h"
#include "timer.h"

cpu_t trap_cpu;

void trap_handler()
{
  uart_printf("trap_handler: Current Ticks: %d\n", mtime());
  set_timeout(10000000);
}