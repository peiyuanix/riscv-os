#include "riscv_asm.h"
#include "uart.h"
#include "timer.h"
#include "interrupts.h"
#include "plic.h"
#include "proc.h"
#include "kstring.h"

void trap_entry();
void test_proc_0();
void test_proc_1();

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

void proc_init()
{
  struct proc test_proc_0 = {
      .name = "test_proc_0",
      .pid = 0,
      .hartid = 0,
      .state = PROC_READY,
      .cpu = {
          .pc = (u64)&test_proc_0,
      }};
  proc_list[0] = test_proc_0;

  struct proc test_proc_1 = {
      .name = "test_proc_1",
      .pid = 1,
      .hartid = 0,
      .state = PROC_READY,
      .cpu = {
          .pc = (u64)&test_proc_1,
      }};
  proc_list[1] = test_proc_1;

  for (int i = 2; i < PROC_TOTAL_COUNT; i++)
  {
    memset(&proc_list[i], 0, sizeof(proc_list[i]));
    proc_list[i].state = PROC_NONE;
  }

  active_pid = -1;
}

void firmware_main()
{
  trap_init();
  uart_init();
  proc_init();
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