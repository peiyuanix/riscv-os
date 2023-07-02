#include "riscv_cpu.h"
#include "uart.h"
#include "timer.h"
#include "proc.h"

struct cpu trap_cpu;

void trap_handler()
{
  u64 mcause = csrr_mcause();
  uart_printf("[trap_handler] active_pid: %d, mcause: 0x%lX, current ticks: %d\n", active_pid, mcause, mtime());
  set_timeout(10000000);
}