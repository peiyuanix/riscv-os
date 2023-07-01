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
  csrw_mie(1 << 7);
  csrw_mstatus(1 << 3);

  uart_printf("default MTIMECMP_0 is %d\n", mtimecmp_0());

  set_timeout(10000000);
  while (1)
  {
  }
}