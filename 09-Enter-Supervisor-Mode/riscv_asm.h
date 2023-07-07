#ifndef _RISCV_ASM_H
#define _RISCV_ASM_H

#include "riscv_arch.h"

#define readu8(addr) (*(const u8 *)(addr))
#define readu16(addr) (*(const u16 *)(addr))
#define readu32(addr) (*(const u32 *)(addr))
#define readu64(addr) (*(const u64 *)(addr))

#define writeu8(addr, val) (*(u8 *)(addr) = (val))
#define writeu16(addr, val) (*(u16 *)(addr) = (val))
#define writeu32(addr, val) (*(u32 *)(addr) = (val))
#define writeu64(addr, val) (*(u64 *)(addr) = (val))

static inline void ecall()
{
  asm volatile("ecall"
               :
               :);
}

// Physical Memory Protection
static inline void w_pmpcfg0(u64 x)
{
  asm volatile("csrw pmpcfg0, %0"
               :
               : "r"(x));
}

static inline void w_pmpaddr0(u64 x)
{
  asm volatile("csrw pmpaddr0, %0"
               :
               : "r"(x));
}

// csr operations
#include "riscv_asm_csr.gen.h"

#endif /* _RISCV_ASM_H */