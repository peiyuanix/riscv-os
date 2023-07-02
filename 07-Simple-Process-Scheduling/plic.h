#ifndef _PLIC_H
#define _PLIC_H

#include "riscv_types.h"
#include "riscv_asm.h"

#define PLIC_INTRID_UART0 4

#define PLIC_PRI_BASE 0x0C000000
#define PLIC_PRI_CALC(intr_id) (PLIC_PRI_BASE + (intr_id)*4)
#define PLIC_PRI_UART0 PLIC_PRI_CALC(PLIC_INTRID_UART0)

#define PLIC_PENDING_R0 0x0C001000
#define PLIC_PENDING_R1 0x0C001004

#define PLIC_MIE_HART0LO 0x0C002000
#define PLIC_MIE_HART0HI 0x0C002004

#define PLIC_PRI_THR 0x0C200000

#define PLIC_INTR_CLAIM 0x0C200004

static inline u32 plic_pri_uart0()
{
  return readu32(PLIC_PRI_UART0);
}

static inline void plic_pri_uart0_write(u32 val)
{
  writeu32(PLIC_PRI_UART0, val);
}

static inline u32 plic_mie_hart0lo()
{
  return readu32(PLIC_MIE_HART0LO);
}

static inline void plic_mie_hart0lo_write(u32 val)
{
  writeu32(PLIC_MIE_HART0LO, val);
}

static inline u32 plic_mie_hart0hi()
{
  return readu32(PLIC_MIE_HART0HI);
}

static inline void plic_mie_hart0hi_write(u32 val)
{
  writeu32(PLIC_MIE_HART0HI, val);
}

static inline u64 plic_mie_hart0()
{
  return (((u64)plic_mie_hart0hi()) << 32) | plic_mie_hart0lo();
}

static inline void plic_mie_hart0_write(u64 val)
{
  plic_mie_hart0lo_write(0xffffffff & val);
  plic_mie_hart0hi_write(val >> 32);
}

static inline u32 plic_pri_thr()
{
  return 0x7 & readu32(PLIC_PRI_THR);
}

static inline void plic_pri_thr_write(u32 val)
{
  writeu32(PLIC_PRI_THR, val);
}

static inline u32 plic_intr_claim()
{
  return readu32(PLIC_INTR_CLAIM);
}

static inline void plic_intr_claim_write(u32 val)
{
  writeu32(PLIC_INTR_CLAIM, val);
}

#endif /* _PLIC_H */