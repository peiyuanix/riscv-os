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
  // initialize UART
  uart_init();

  // prepare processes
  proc_init();

  // setup timer timout
  uart_printf("[firmware_main] default MTIMECMP_1 is %d\n", mtimecmp_1());
  set_timeout(10000000);

  // // setup S-mode trap vector
  csrw_stvec((u64)strap_entry);
  // // enable SIE in sstatus
  // csrs_sstatus(MSTATUS_SIE);

  // csrc_mstatus(MSTATUS_MIE | MSTATUS_SIE);
  // uart_printf("[firmware_main] mstatus is 0x%x\n", csrr_mstatus());

  // setup M-mode trap vector
  csrw_mtvec((u64)mtrap_entry);
  // enable M-mode timer interrupt
  csrw_mie(MIE_MTIE);
  // delegate interrupts
  // csrw_mideleg(MIE_MTIE | MIE_STIE);
  // enable MPIE in mstatus
  // csrs_mstatus(MSTATUS_MPP_U);

  // csrw_medeleg(MEDELEG_S_ECALL | MEDELEG_U_ECALL);

  // csrw_mepc((u64)infi);

  uart_printf("[firmware_main] Clear mie\n");
  csrw_mie(0x0);
  uart_printf("[firmware_main] mie is 0x%x\n", csrr_mie());
  uart_printf("[firmware_main] sie is 0x%x\n", csrr_sie());
  uart_printf("[firmware_main] Set MIE_SEIE | MIE_STIE | MIE_SSIE for mie\n");
  csrs_mie(MIE_SEIE | MIE_STIE | MIE_SSIE | MIE_MEIE);
  uart_printf("[firmware_main] mie is 0x%x\n", csrr_mie());
  uart_printf("[firmware_main] sie is 0x%x\n", csrr_sie());
  uart_printf("[firmware_main] mideleg is 0x%x\n", csrr_mideleg());
  // uart_printf("[firmware_main] Set MIE_SEIE | MIE_STIE | MIE_SSIE for mideleg\n");
  // csrs_mideleg(MIE_SEIE | MIE_STIE);
  // uart_printf("[firmware_main] mie is 0x%x\n", csrr_mie());
  // uart_printf("[firmware_main] sie is 0x%x\n", csrr_sie());
  // uart_printf("[firmware_main] Set MIE_SSIE for mideleg\n");
  // csrs_mideleg(MIE_SSIE);
  // uart_printf("[firmware_main] mie is 0x%x\n", csrr_mie());
  // uart_printf("[firmware_main] sie is 0x%x\n", csrr_sie());

  uart_printf("[firmware_main] Set MIE_SSIE for sie\n");
  csrs_sie(MIE_MEIE | MIE_MSIE | MIE_MTIE);
  uart_printf("[firmware_main] mie is 0x%x\n", csrr_mie());
  uart_printf("[firmware_main] sie is 0x%x\n", csrr_sie());

  // uart_printf("[firmware_main] Clear MSTATUS_MIE | MSTATUS_SIE for mstatus\n");
  // csrc_mstatus(MSTATUS_MIE | MSTATUS_SIE);
  // uart_printf("[firmware_main] mstatus is 0x%x\n", csrr_mstatus());
  // uart_printf("[firmware_main] sstatus is 0x%x\n", csrr_sstatus());
  // uart_printf("[firmware_main] Set SSTATUS_SIE for sstatus\n");
  // csrs_sstatus(SSTATUS_SIE);
  // uart_printf("[firmware_main] mstatus is 0x%x\n", csrr_mstatus());
  // uart_printf("[firmware_main] sstatus is 0x%x\n", csrr_sstatus());

  while (1)
    ;

  asm volatile("mret");
}