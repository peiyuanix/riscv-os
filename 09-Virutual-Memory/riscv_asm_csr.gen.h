#ifndef _RISCV_ASM_CSR_H
#define _RISCV_ASM_CSR_H

#include "riscv_arch.h"

static inline u64 csrr_mstatus()
{
  volatile u64 val;
  asm volatile("csrr %0, mstatus"
               : "=r"(val)
               :);
  return val;
}

static inline void csrw_mstatus(const volatile u64 val)
{
  asm volatile("csrw mstatus, %0"
               :
               : "r"(val));
}

static inline void csrs_mstatus(const volatile u64 val)
{
  asm volatile("csrs mstatus, %0"
               :
               : "r"(val));
}

static inline void csrc_mstatus(const volatile u64 val)
{
  asm volatile("csrc mstatus, %0"
               :
               : "r"(val));
}

static inline u64 csrr_mie()
{
  volatile u64 val;
  asm volatile("csrr %0, mie"
               : "=r"(val)
               :);
  return val;
}

static inline void csrw_mie(const volatile u64 val)
{
  asm volatile("csrw mie, %0"
               :
               : "r"(val));
}

static inline void csrs_mie(const volatile u64 val)
{
  asm volatile("csrs mie, %0"
               :
               : "r"(val));
}

static inline void csrc_mie(const volatile u64 val)
{
  asm volatile("csrc mie, %0"
               :
               : "r"(val));
}

static inline u64 csrr_mip()
{
  volatile u64 val;
  asm volatile("csrr %0, mip"
               : "=r"(val)
               :);
  return val;
}

static inline void csrw_mip(const volatile u64 val)
{
  asm volatile("csrw mip, %0"
               :
               : "r"(val));
}

static inline void csrs_mip(const volatile u64 val)
{
  asm volatile("csrs mip, %0"
               :
               : "r"(val));
}

static inline void csrc_mip(const volatile u64 val)
{
  asm volatile("csrc mip, %0"
               :
               : "r"(val));
}

static inline u64 csrr_mideleg()
{
  volatile u64 val;
  asm volatile("csrr %0, mideleg"
               : "=r"(val)
               :);
  return val;
}

static inline void csrw_mideleg(const volatile u64 val)
{
  asm volatile("csrw mideleg, %0"
               :
               : "r"(val));
}

static inline void csrs_mideleg(const volatile u64 val)
{
  asm volatile("csrs mideleg, %0"
               :
               : "r"(val));
}

static inline void csrc_mideleg(const volatile u64 val)
{
  asm volatile("csrc mideleg, %0"
               :
               : "r"(val));
}

static inline u64 csrr_medeleg()
{
  volatile u64 val;
  asm volatile("csrr %0, medeleg"
               : "=r"(val)
               :);
  return val;
}

static inline void csrw_medeleg(const volatile u64 val)
{
  asm volatile("csrw medeleg, %0"
               :
               : "r"(val));
}

static inline void csrs_medeleg(const volatile u64 val)
{
  asm volatile("csrs medeleg, %0"
               :
               : "r"(val));
}

static inline void csrc_medeleg(const volatile u64 val)
{
  asm volatile("csrc medeleg, %0"
               :
               : "r"(val));
}

static inline u64 csrr_mcause()
{
  volatile u64 val;
  asm volatile("csrr %0, mcause"
               : "=r"(val)
               :);
  return val;
}

static inline void csrw_mcause(const volatile u64 val)
{
  asm volatile("csrw mcause, %0"
               :
               : "r"(val));
}

static inline u64 csrr_mtvec()
{
  volatile u64 val;
  asm volatile("csrr %0, mtvec"
               : "=r"(val)
               :);
  return val;
}

static inline void csrw_mtvec(const volatile u64 val)
{
  asm volatile("csrw mtvec, %0"
               :
               : "r"(val));
}

static inline u64 csrr_mepc()
{
  volatile u64 val;
  asm volatile("csrr %0, mepc"
               : "=r"(val)
               :);
  return val;
}

static inline void csrw_mepc(const volatile u64 val)
{
  asm volatile("csrw mepc, %0"
               :
               : "r"(val));
}

static inline u64 csrr_sstatus()
{
  volatile u64 val;
  asm volatile("csrr %0, sstatus"
               : "=r"(val)
               :);
  return val;
}

static inline void csrw_sstatus(const volatile u64 val)
{
  asm volatile("csrw sstatus, %0"
               :
               : "r"(val));
}

static inline void csrs_sstatus(const volatile u64 val)
{
  asm volatile("csrs sstatus, %0"
               :
               : "r"(val));
}

static inline void csrc_sstatus(const volatile u64 val)
{
  asm volatile("csrc sstatus, %0"
               :
               : "r"(val));
}

static inline u64 csrr_sie()
{
  volatile u64 val;
  asm volatile("csrr %0, sie"
               : "=r"(val)
               :);
  return val;
}

static inline void csrw_sie(const volatile u64 val)
{
  asm volatile("csrw sie, %0"
               :
               : "r"(val));
}

static inline void csrs_sie(const volatile u64 val)
{
  asm volatile("csrs sie, %0"
               :
               : "r"(val));
}

static inline void csrc_sie(const volatile u64 val)
{
  asm volatile("csrc sie, %0"
               :
               : "r"(val));
}

static inline u64 csrr_sip()
{
  volatile u64 val;
  asm volatile("csrr %0, sip"
               : "=r"(val)
               :);
  return val;
}

static inline void csrw_sip(const volatile u64 val)
{
  asm volatile("csrw sip, %0"
               :
               : "r"(val));
}

static inline void csrs_sip(const volatile u64 val)
{
  asm volatile("csrs sip, %0"
               :
               : "r"(val));
}

static inline void csrc_sip(const volatile u64 val)
{
  asm volatile("csrc sip, %0"
               :
               : "r"(val));
}

static inline u64 csrr_scause()
{
  volatile u64 val;
  asm volatile("csrr %0, scause"
               : "=r"(val)
               :);
  return val;
}

static inline void csrw_scause(const volatile u64 val)
{
  asm volatile("csrw scause, %0"
               :
               : "r"(val));
}

static inline u64 csrr_stvec()
{
  volatile u64 val;
  asm volatile("csrr %0, stvec"
               : "=r"(val)
               :);
  return val;
}

static inline void csrw_stvec(const volatile u64 val)
{
  asm volatile("csrw stvec, %0"
               :
               : "r"(val));
}

static inline u64 csrr_sepc()
{
  volatile u64 val;
  asm volatile("csrr %0, sepc"
               : "=r"(val)
               :);
  return val;
}

static inline void csrw_sepc(const volatile u64 val)
{
  asm volatile("csrw sepc, %0"
               :
               : "r"(val));
}

static inline u64 csrr_pmpaddr0()
{
  volatile u64 val;
  asm volatile("csrr %0, pmpaddr0"
               : "=r"(val)
               :);
  return val;
}

static inline void csrw_pmpaddr0(const volatile u64 val)
{
  asm volatile("csrw pmpaddr0, %0"
               :
               : "r"(val));
}

static inline u64 csrr_pmpcfg0()
{
  volatile u64 val;
  asm volatile("csrr %0, pmpcfg0"
               : "=r"(val)
               :);
  return val;
}

static inline void csrw_pmpcfg0(const volatile u64 val)
{
  asm volatile("csrw pmpcfg0, %0"
               :
               : "r"(val));
}

#endif /* _RISCV_ASM_CSR_H */
