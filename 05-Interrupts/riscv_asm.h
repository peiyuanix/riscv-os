#ifndef _RISCV_ASM_H
#define _RISCV_ASM_H

#include "riscv_types.h"

#define readu8(addr) (*(const u8 *)(addr))
#define readu16(addr) (*(const u16 *)(addr))
#define readu32(addr) (*(const u32 *)(addr))
#define readu64(addr) (*(const u64 *)(addr))

#define writeu8(addr, val) (*(u8 *)(addr) = (val))
#define writeu16(addr, val) (*(u16 *)(addr) = (val))
#define writeu32(addr, val) (*(u32 *)(addr) = (val))
#define writeu64(addr, val) (*(u64 *)(addr) = (val))

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