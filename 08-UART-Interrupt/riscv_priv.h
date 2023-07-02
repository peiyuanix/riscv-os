#ifndef _RISCV_PRIV_H
#define _RISCV_PRIV_H

#include "riscv_asm.h"

#define MSTATUS_SPP_U (0x1UL << 8)

static inline void mstatus_set_spp_to_u(void)
{
  u64 mstatus = csrr_mstatus();
  mstatus &= ~MSTATUS_SPP_U;
  mstatus |= MSTATUS_SPP_U;
  csrw_mstatus(mstatus);
}

#endif /* _RISCV_PRIV_H */