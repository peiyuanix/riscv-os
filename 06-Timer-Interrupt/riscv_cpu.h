#ifndef _CPU_H
#define _CPU_H

#include "riscv_types.h"

struct cpu
{
  u64 x0;  // zero
  u64 x1;  // ra
  u64 x2;  // sp
  u64 x3;  // gp
  u64 x4;  // tp
  u64 x5;  // t0
  u64 x6;  // t1
  u64 x7;  // t2
  u64 x8;  // s0/fp
  u64 x9;  // s1
  u64 x10; // a0
  u64 x11; // a1
  u64 x12; // a2
  u64 x13; // a3
  u64 x14; // a4
  u64 x15; // a5
  u64 x16; // a6
  u64 x17; // a7
  u64 x18; // s2
  u64 x19; // s3
  u64 x20; // s4
  u64 x21; // s5
  u64 x22; // s6
  u64 x23; // s7
  u64 x24; // s8
  u64 x25; // s9
  u64 x26; // s10
  u64 x27; // s11
  u64 x28; // t3
  u64 x29; // t4
  u64 x30; // t5
  u64 x31; // t6

  u64 pc; // pc
} __attribute__((packed));

#endif /* _CPU_H */