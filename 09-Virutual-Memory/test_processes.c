#include "riscv_arch.h"
#include "uart.h"

#define INTERVAL 100000000

u8 test_proc_0_stack[1 << 20];
void *test_proc_0_stack_top = &test_proc_0_stack[sizeof(test_proc_0_stack) - 1];

void test_proc_0_entry()
{
  while (true)
  {
    for (size_t i = 0; i < INTERVAL; i++)
    {
    }
    uart_printf("[PID = %d] Hello, Process Shceduler!\n", 0);
  }
}

u8 test_proc_1_stack[1 << 20];
void *test_proc_1_stack_top = &test_proc_1_stack[sizeof(test_proc_1_stack) - 1];

void test_proc_1_entry()
{
  while (true)
  {
    for (size_t i = 0; i < INTERVAL; i++)
    {
    }
    uart_printf("[PID = %d] Hello, Process Shceduler!\n", 1);
    asm volatile ("ecall");
  }
}

u8 test_proc_2_stack[1 << 20];
void *test_proc_2_stack_top = &test_proc_2_stack[sizeof(test_proc_2_stack) - 1];
void test_proc_2_entry()
{
  while (true)
  {
    for (size_t i = 0; i < INTERVAL; i++)
    {
    }
    uart_printf("[PID = %d] Hello, Process Shceduler!\n", 2);
  }
}
