#ifndef _PROC_H
#define _PROC_H

#define PROC_NAME_MAXLEN 64
#define PROC_TOTAL_COUNT 16

#include "riscv_types.h"
#include "riscv_cpu.h"

enum proc_state
{
  PROC_STATE_NONE = 0,
  PROC_STATE_READY,
  PROC_STATE_RUNNING,
};

struct proc
{
  enum proc_state state;
  u32 pid;
  u8 name[PROC_NAME_MAXLEN];
  struct cpu cpu;
  u64 hartid;
};

extern i32 active_pid;
extern struct proc proc_list[PROC_TOTAL_COUNT];

#endif /* _PROC_H */