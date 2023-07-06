#ifndef _TIMER_H
#define _TIMER_H

#include "riscv_asm.h"

#define MTIME 0x200bff8
#define MTIMECMP_1 0x2004008

static inline u64 mtime()
{
  return readu64(MTIME);
}

static inline u64 mtimecmp_1()
{
  return readu64(MTIMECMP_1);
}

static inline u64 set_timeout(u64 timeout)
{
  writeu64(MTIMECMP_1, mtime() + timeout);
}

#endif