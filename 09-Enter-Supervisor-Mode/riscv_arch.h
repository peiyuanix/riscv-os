#ifndef _RISCV_ARCH_H
#define _RISCV_ARCH_H

// machine bits
#define MACHINE_BITS 64
#define BITS_PER_LONG MACHINE_BITS

// bool
#define bool _Bool
#define true 1
#define false 0

// unsigned types
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long u64;

// signed types
typedef signed char i8;
typedef signed short i16;
typedef signed int i32;
typedef signed long i64;

// size_t
typedef u64 size_t;

#endif /* _RISCV_ARCH_H */