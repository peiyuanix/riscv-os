#include "riscv_types.h"

u8 test_proc_0_stack[1 << 20];
void *test_proc_0_stack_top = &test_proc_0_stack[sizeof(test_proc_0_stack) - 1];

void test_proc_0_entry()
{
  while (true)
  {
  }
}

u8 test_proc_1_stack[1 << 20];
void *test_proc_1_stack_top = &test_proc_1_stack[sizeof(test_proc_1_stack) - 1];

void test_proc_1_entry()
{
  while (true)
  {
  }
}

u8 test_proc_2_stack[1 << 20];
void *test_proc_2_stack_top = &test_proc_2_stack[sizeof(test_proc_2_stack) - 1];
void test_proc_2_entry()
{
  while (true)
  {
  }
}
