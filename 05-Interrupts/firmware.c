#include "riscv_asm.h"
#include "uart.h"
#include "timer.h"
#include "interrupts.h"
#include "plic.h"

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

  uart_printf("plic_pri_thr is 0x%x\n", plic_pri_thr());
  plic_pri_thr_write(0x0);
  uart_printf("plic_pri_thr is 0x%x\n", plic_pri_thr());

  uart_printf("plic_pri_uart0 is 0x%x\n", plic_pri_uart0());
  plic_pri_uart0_write(0x7);
  uart_printf("plic_pri_uart0 is 0x%x\n", plic_pri_uart0());

  uart_printf("plic_mie_hart0 is 0x%x\n", plic_mie_hart0());
  plic_mie_hart0_write(1 << PLIC_INTRID_UART0);
  uart_printf("plic_mie_hart0 is 0x%x\n", plic_mie_hart0());

  uart_printf("_uart_ie is 0x%x\n", _uart_ie());
  _uart_ie_write(UART_IE_RXWM);
  uart_printf("_uart_ie is 0x%x\n", _uart_ie());

  uart_printf("default MTIMECMP_0 is %d\n", mtimecmp_0());
  set_timeout(10000000);

  csrw_mie(MIE_MTIE | MIE_MEIE);
  csrs_mstatus(MSTAUTS_MIE);

  while (1)
  {
  }
}