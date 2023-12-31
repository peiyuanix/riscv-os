#ifndef _INTERRUPTS_H
#define _INTERRUPTS_H

#include "riscv_arch.h"

/* Machine Mode Registers */
// mstatus
#define MSTATUS_SIE (0x1L << 1)
#define MSTATUS_MIE (0x1L << 3)
#define MSTATUS_SPIE (0x1L << 5)
#define MSTATUS_MPIE (0x1L << 7)
#define MSTATUS_SPP_U (0x0L << 8)
#define MSTATUS_SPP_S (0x1L << 8)
#define MSTATUS_SPP_MASK (0x1L << 8)
#define MSTATUS_MPP_U (0x0L << 11)
#define MSTATUS_MPP_S (0x1L << 11)
#define MSTATUS_MPP_M (0x3L << 11)
#define MSTATUS_MPP_MASK (0x3L << 11)

// mie
#define MIE_SSIE (0x1L << 1)
#define MIE_MSIE (0x1L << 3)
#define MIE_STIE (0x1L << 5)
#define MIE_MTIE (0x1L << 7)
#define MIE_SEIE (0x1L << 9)
#define MIE_MEIE (0x1L << 11)

// mip
#define MIP_SSIP MIE_SSIE
#define MIP_MSIP MIE_MSIE
#define MIP_STIP MIE_STIE
#define MIP_MTIP MIE_MTIE
#define MIP_SEIP MIE_SEIE
#define MIP_MEIP MIE_MEIE

// medeleg
#define MEDELEG_U_ECALL (1L << 8)
#define MEDELEG_S_ECALL (1L << 9)
#define MEDELEG_M_ECALL (1L << 11)

// mcause
#define MCAUSE_INTR_FLAG (0x1L << (MACHINE_BITS - 1))
#define MCAUSE_INTR_S_SOFT (MCAUSE_INTR_FLAG | 1)
#define MCAUSE_INTR_M_SOFT (MCAUSE_INTR_FLAG | 3)
#define MCAUSE_INTR_S_TIMER (MCAUSE_INTR_FLAG | 5)
#define MCAUSE_INTR_M_TIMER (MCAUSE_INTR_FLAG | 7)
#define MCAUSE_INTR_S_EXTER (MCAUSE_INTR_FLAG | 9)
#define MCAUSE_INTR_M_EXTER (MCAUSE_INTR_FLAG | 11)
#define MCAUSE_INNER_ILLEAGEL_INSTRUCTION (0x2L)
#define MCAUSE_INNER_U_ECALL (8L)
#define MCAUSE_INNER_S_ECALL (9L)
#define MCAUSE_INNER_M_ECALL (11L)

/* Supervisor Mode Registers */
// sstatus
#define SSTATUS_SIE MSTATUS_SIE
#define SSTATUS_SPIE MSTATUS_SPIE
#define SSTATUS_SPP_U MSTATUS_SPP_U
#define SSTATUS_SPP_S MSTATUS_SPP_S
#define SSTATUS_SPP_MASK MSTATUS_SPP_MASK
// sie
#define SIE_SSIE MIE_SSIE
#define SIE_STIE MIE_STIE
#define SIE_SEIE MIE_SEIE
// sip
#define SIP_SSIP SIE_SSIE
#define SIP_STIP SIE_STIE
#define SIP_SEIP SIE_SEIE

#endif /* _INTERRUPTS_H */