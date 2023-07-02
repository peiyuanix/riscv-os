#include "riscv_asm.h"
#include "uart.h"
#include "timer.h"
#include "interrupts.h"

extern void trap_entry();

void trap_init()
{
  csrw_mtvec((u64)trap_entry);
}

void uart_interrupt_setup()
{
  u32 u32val = _uart_ie();
  _uart_ie_write(UART_IE_RXWM);
  uart_printf("[uart_interrupt_setup] _uart_ie => 0x%X => 0x%X\n", u32val, _uart_ie());
}

void firmware_main()
{
  trap_init();

  uart_printf("default MTIMECMP_0 is %d\n", mtimecmp_0());
  set_timeout(10000000);

  csrw_mie(MIE_MTIE);
  csrs_mstatus(MSTAUTS_MIE);

  while (1)
  {
  }
}