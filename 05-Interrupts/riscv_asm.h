#ifndef _RISCV_ASM_H
#define _RISCV_ASM_H

#include "riscv_types.h"

static inline void write4b(u32 val, volatile void *addr)
{
  asm volatile("sw %0, 0(%1)"
               :
               : "r"(val), "r"(addr));
}

static inline u32 read4b(const volatile void *addr)
{
  u32 val;
  asm volatile("lw %0, 0(%1)"
               : "=r"(val)
               : "r"(addr));
  return val;
}

static inline u64 read8b(const volatile void *addr)
{
  u64 val;
  asm volatile("ld %0, 0(%1)"
               : "=r"(val)
               : "r"(addr));
  return val;
}

static inline void csrw_mtvec(const volatile u64 val)
{
  asm volatile("csrw mtvec, %0"
               :
               : "r"(val));
}

static inline void ecall()
{
  asm volatile("ecall"
               :
               :);
}

#endif