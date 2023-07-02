#ifndef _INTERRUPTS_H
#define _INTERRUPTS_H

#include "riscv_arch.h"

#define MSTAUTS_MIE (0x1L << 3)

#define MIE_MTIE (0x1L << 7)

#define MCAUSE_INTR_M_TIMER ((0x1L << (MACHINE_BITS - 1)) | 7)

#endif /* _INTERRUPTS_H */