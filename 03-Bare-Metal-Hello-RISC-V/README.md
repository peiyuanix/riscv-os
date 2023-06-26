# 03: Bare Metal Hello RISC-V

# TODO

## Background

### How does RISC-V boot?

### QEMU RISC-V *virt* Memory Map

### UART of *virt*

### 

## Utils

### RISC-V Assembly

### Useful Tools

- as - The GNU Assembler
- ld - The GNU Linker
- objcopy - copy and translate object files
- dtc - Device Tree Compiler

## Hello, RISC-V!

### Write UART Driver for *virt*

### Boot

## References
- [QEMU Manual - Boot Image or Kernel specific](https://www.qemu.org/docs/master/system/invocation.html#hxtool-8)
- [QEMU Manual - RISC-V CPU firmware](https://www.qemu.org/docs/master/system/target-riscv.html#risc-v-cpu-firmware)
- [QEMU Manual - RISC-V Generic Virtual Platform](https://www.qemu.org/docs/master/system/riscv/virt.html)
- [QEMU RISC-V virt Machine Source Code](https://github.com/qemu/qemu/blob/master/hw/riscv/virt.c)
- [QEMU RISC-V Boot Helper Source Code](https://github.com/qemu/qemu/blob/master/hw/riscv/boot.c)
- [OpenSBI Platform Firmwares](https://github.com/riscv-software-src/opensbi/blob/master/docs/firmware/fw.md)
- [The GNU assembler](https://ftp.gnu.org/old-gnu/Manuals/gas-2.9.1/html_node/as_toc.html#TOC3)
- [The GNU Linker - Command Language](https://ftp.gnu.org/old-gnu/Manuals/ld-2.9.1/html_chapter/ld_3.html#SEC5)
- [objcopy - copy and translate object files](https://ftp.gnu.org/old-gnu/Manuals/binutils-2.12/html_node/binutils_5.html)
- [RISC-V Assembly Programmer's Manual](https://github.com/riscv-non-isa/riscv-asm-manual/blob/master/riscv-asm.md)
- [**OpenSBI UART-8250 Driver - Compatible with NS16550 of RISC-V virt**](https://github.com/riscv-software-src/opensbi/blob/master/lib/utils/serial/uart8250.c)
- [PC16550D Universal Asynchronous Receiver/Transmitter With FIFOs
](https://media.digikey.com/pdf/Data%20Sheets/Texas%20Instruments%20PDFs/PC16550D.pdf)
- [RISC-V from scratch 2: Hardware layouts, linker scripts, and C runtimes](https://twilco.github.io/riscv-from-scratch/2019/04/27/riscv-from-scratch-2.html)
- [QEMU RISC-V virt 平台分析](https://juejin.cn/post/6891922292075397127)