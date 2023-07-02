#include "riscv_asm.h"
#include "uart.h"
#include "timer.h"
#include "interrupts.h"
#include "plic.h"
#include "proc.h"
#include "kstring.h"

extern void trap_entry();
extern void test_proc_0_entry();
extern void test_proc_1_entry();
extern u64 test_proc_0_stack_top[];
extern u64 test_proc_1_stack_top[];

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

void plic_init()
{
  u32 u32val = plic_pri_thr();
  plic_pri_thr_write(0x0);
  uart_printf("[plic_init] plic_pri_thr 0x%X => 0x%X\n", u32val, plic_pri_thr());

  u32val = plic_pri_uart0();
  plic_pri_uart0_write(0x7);
  uart_printf("[plic_init] plic_pri_uart0 0x%X => 0x%X\n", u32val, plic_pri_uart0());

  u64 u64val = plic_mie_hart0();
  plic_mie_hart0_write(1 << PLIC_INTRID_UART0);
  uart_printf("[plic_init] plic_mie_hart0 0x%X => 0x%X\n", u64val, plic_mie_hart0());
}

void uart_interrupt_setup()
{
  u32 u32val = _uart_ie();
  _uart_ie_write(UART_IE_RXWM);
  uart_printf("[uart_interrupt_setup] _uart_ie => 0x%X => 0x%X\n", u32val, _uart_ie());
}

void proc_init()
{
  struct proc test_proc_0 = {
      .name = "test_proc_0",
      .pid = 0,
      .hartid = 0,
      .state = PROC_STATE_READY,
      .cpu = {
          .pc = (u64)test_proc_0_entry,
          .x2 = (u64)test_proc_0_stack_top,
      }};
  uart_printf("[proc_init] test_proc_0: pc is 0x%lx, stack_top is 0x%lx\n", &test_proc_0, test_proc_0_stack_top);
  proc_list[0] = test_proc_0;

  struct proc test_proc_1 = {
      .name = "test_proc_1",
      .pid = 1,
      .hartid = 0,
      .state = PROC_STATE_READY,
      .cpu = {
          .pc = (u64)test_proc_1_entry,
          .x2 = (u64)test_proc_1_stack_top,
      }};
  uart_printf("[proc_init] test_proc_1: pc is 0x%lx, stack_top is 0x%lx\n", &test_proc_1, test_proc_1_stack_top);
  proc_list[1] = test_proc_1;

  for (int i = 2; i < PROC_TOTAL_COUNT; i++)
  {
    memset(&proc_list[i], 0, sizeof(proc_list[i]));
    proc_list[i].state = PROC_STATE_NONE;
  }

  active_pid = -1;
}

void firmware_main()
{
  trap_init();
  uart_init();
  proc_init();
  plic_init();
  uart_interrupt_setup();
  // ecall();
  // echo();

  uart_printf("default MTIMECMP_0 is %d\n", mtimecmp_0());
  set_timeout(10000000);

  csrw_mie(MIE_MTIE | MIE_MEIE);
  csrs_mstatus(MSTAUTS_MIE);

  while (1)
  {
  }
}