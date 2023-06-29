#ifndef _TIMER_H
#define _TIMER_H

#include "riscv_asm.h"

#define MTIME 0x200bff8

static inline u64 mtime() {
  return read8b((void *)MTIME);
}

#endif