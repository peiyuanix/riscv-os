#include "riscv_asm.h"
#include "uart.h"
#include "timer.h"

void trap_entry();

void echo()
{
  uart_print("Hello, RISC-V!\n");
  uart_print("echo> ");
  for (;;)
  {
    u32 data = uart_getc();
    if (!(data & UART_RXFIFO_EMPTY))
    {
      uart_putc(data & UART_RXFIFO_DATA);
    }
  }
}

void trap_init()
{
  csrw_mtvec((u64)trap_entry);
}

void firmware_main()
{
  trap_init();
  uart_init();
  // ecall();
  // echo();
  u64 prev_mtime;
  u64 curr_mtime;
  while (1)
  {
    for (u32 i = 0; i < 300000000; i++)
    {
    }
    curr_mtime = mtime();
    uart_printf("Current Ticks: %d, Ticks Delta: %d\n", curr_mtime, curr_mtime - prev_mtime);
    prev_mtime = curr_mtime;
    set_timeout(10000000);
  }

}