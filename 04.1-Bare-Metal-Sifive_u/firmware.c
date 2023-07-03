#include "uart.h"

void firmware_main()
{
  uart_init();
  uart_print("Hello, Sifive_u!\n");
  uart_print("echo> ");
  while (1)
  {
    u32 rxdata = uart_getc();
    if (!(rxdata & UART_RXFIFO_EMPTY))
    {
      uart_putc(rxdata & 0xff);
    }
  }
}