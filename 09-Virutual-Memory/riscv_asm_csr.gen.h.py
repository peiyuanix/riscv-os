def csrr(reg):
    return f'''
static inline u64 csrr_{reg}()
{{
  volatile u64 val;
  asm volatile("csrr %0, {reg}"
               : "=r"(val)
               :);
  return val;
}}'''


def csrw(reg):
    return f'''
static inline void csrw_{reg}(const volatile u64 val)
{{
  asm volatile("csrw {reg}, %0"
               :
               : "r"(val));
}}'''


def csrs(reg):
    return f'''
static inline void csrs_{reg}(const volatile u64 val)
{{
  asm volatile("csrs {reg}, %0"
               :
               : "r"(val));
}}'''


def csrc(reg):
    return f'''
static inline void csrc_{reg}(const volatile u64 val)
{{
  asm volatile("csrc {reg}, %0"
               :
               : "r"(val));
}}'''


registers = {
    # M-mode csr registers
    "mstatus": [csrr, csrw, csrs, csrc],
    "mie": [csrr, csrw, csrs, csrc],
    "mip": [csrr, csrw, csrs, csrc],
    "mideleg": [csrr, csrw, csrs, csrc],
    "medeleg": [csrr, csrw, csrs, csrc],
    "mcause": [csrr, csrw],
    "mtvec": [csrr, csrw],
    "mepc": [csrr, csrw],
    # S-mode csr registers
    "sstatus": [csrr, csrw, csrs, csrc],
    "sie": [csrr, csrw, csrs, csrc],
    "sip": [csrr, csrw, csrs, csrc],
    "scause": [csrr, csrw],
    "stvec": [csrr, csrw],
    "sepc": [csrr, csrw],
    # Physical memory protection
    "pmpaddr0": [csrr, csrw],
    "pmpcfg0": [csrr, csrw],
}


def main():
    print("#ifndef _RISCV_ASM_CSR_H")
    print("#define _RISCV_ASM_CSR_H")
    print("")
    print('#include "riscv_arch.h"')

    for reg, ops in registers.items():
        for op in ops:
            print(op(reg))

    print()
    print("#endif /* _RISCV_ASM_CSR_H */")


if __name__ == '__main__':
    main()
