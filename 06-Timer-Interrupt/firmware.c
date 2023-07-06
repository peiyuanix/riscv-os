#include "riscv_asm.h"
#include "uart.h"
#include "timer.h"
#include "interrupts.h"

extern void trap_entry();

void firmware_main()
{
  uart_init();

  // setup timer timout
  uart_printf("[firmware_main] default MTIMECMP_1 is %d\n", mtimecmp_1());
  set_timeout(10000000);

  // setup M-mode trap vector
  csrw_mtvec((u64)trap_entry);
  // enable M-mode timer interrupt
  csrw_mie(MIE_MTIE);
  // enable MIE in mstatus
  csrs_mstatus(MSTAUTS_MIE);

  while (1)
  {
  }
}