#include "riscv_asm.h"
#include "uart.h"
#include "timer.h"
#include "riscv_priv.h"
#include "proc.h"
#include "kstring.h"

extern void mtrap_entry();
extern void strap_entry();
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

void __attribute__((naked)) infi()
{
  while (1)
  {
  }
}

void firmware_main()
{
  // print initial status
  uart_printf("[firmware_main] mstatus: 0x%x\n", csrr_mstatus());
  uart_printf("[firmware_main] mie: 0x%x\n", csrr_mie());
  uart_printf("[firmware_main] mip: 0x%x\n", csrr_mip());
  uart_printf("[firmware_main] mtimecmp_1: %ld\n", mtimecmp_1());

  // initialize UART
  uart_init();

  // prepare processes
  proc_init();

  // setup timer timout
  set_timeout(1000000);

  // setup S-mode trap vector
  csrw_stvec((u64)strap_entry);

  // setup M-mode trap vector
  csrw_mtvec((u64)mtrap_entry);
  // enable M-mode timer interrupt
  csrw_mie(MIE_MTIE | MIE_SEIE | MIE_SSIE | MIE_STIE);
  // delegate all possible interrupts and exceptions
  csrw_mideleg(~0UL);
  csrw_medeleg(~0UL);
  uart_printf("[firmware_main] mideleg: 0x%lx\n", csrr_mideleg());
  uart_printf("[firmware_main] medeleg: 0x%lx\n", csrr_medeleg());
  uart_printf("[firmware_main] mie: 0x%lx\n", csrr_mie());
  uart_printf("[firmware_main] sie: 0x%lx\n", csrr_sie());

  // setup physical memory protection
  // give S-mode access to the whole address memory space
  csrw_pmpaddr0(~0UL);
  csrw_pmpcfg0(0x0f);

  // set MPP
  csrs_mstatus(MSTATUS_MPIE | MSTATUS_MPP_U);
  csrw_mepc((u64)infi);
  asm volatile("mret");
}