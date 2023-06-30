#ifndef _TIMER_H
#define _TIMER_H

#include "riscv_asm.h"

#define MTIME 0x200bff8
#define MTIMECMP_0 0x2004000

static inline u64 mtime()
{
  return readu64(MTIME);
}

static inline u64 set_timeout(u64 timeout)
{
  writeu64(MTIMECMP_0, mtime() + timeout);
}

#endif