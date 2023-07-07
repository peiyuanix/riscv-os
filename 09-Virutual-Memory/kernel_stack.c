#include "riscv_arch.h"

u8 kernel_stack[1 << 20];
void *kernel_stack_top = &kernel_stack[sizeof(kernel_stack) - 1];