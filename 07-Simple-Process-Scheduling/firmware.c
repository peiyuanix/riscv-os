#include "riscv_asm.h"
#include "uart.h"
#include "timer.h"
#include "interrupts.h"
#include "proc.h"
#include "kstring.h"

extern void trap_entry();
extern void test_proc_0_entry();
extern void test_proc_1_entry();
extern void test_proc_2_entry();
extern void *test_proc_0_stack_top;
extern void *test_proc_1_stack_top;
extern void *test_proc_2_stack_top;

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

  struct proc test_proc_2 = {
      .name = "test_proc_2",
      .pid = 2,
      .hartid = 0,
      .state = PROC_STATE_READY,
      .cpu = {
          .pc = (u64)test_proc_2_entry,
          .x2 = (u64)test_proc_2_stack_top,
      }};
  uart_printf("[proc_init] test_proc_2: pc is 0x%lx, stack_top is 0x%lx\n", &test_proc_2, test_proc_2_stack_top);
  proc_list[2] = test_proc_2;

  for (int i = 3; i < PROC_TOTAL_COUNT; i++)
  {
    memset(&proc_list[i], 0, sizeof(proc_list[i]));
    proc_list[i].state = PROC_STATE_NONE;
  }

  active_pid = -1;
}

void firmware_main()
{
  // initialize UART
  uart_init();

  // prepare processes
  proc_init();

  // setup timer timout
  uart_printf("[firmware_main] default MTIMECMP_0 is %d\n", mtimecmp_0());
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