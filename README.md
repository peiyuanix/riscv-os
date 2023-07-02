# Build a minimal kernel for RISC-V

## Part 1. Explore RISC-V/QEMU/U-Boot/OpenSBI

Get familiar with QEMU virtual machine firmware loading, kernel loading workflow.

- [00: Run Linux with QEMU](/00-Run-Linux-With-QEMU)  
- [01: Run U-Boot with QEMU](/01-Run-U-Boot-With-QEMU)  
- [02: Run OpenSBI with QEMU](/02-Run-OpenSBI-With-QEMU)  

## Part 2. Bare Metal RISC-V

Write a bare metal firmware for QEMU `virt` device, which just prints `Hello, RISC-V!`  

- [03: Bare Metal Hello RISC-V](/03-Bare-Metal-Hello-RISC-V)  
- [04: Bare Metal Hello RISC-V (C Language Version)](/04-Bare-Metal-C-Language)

**Switch to `sifive_u`, because `virt` is not well documented!**  

**Attention: _sifive_u_ has multiple cores!** When I first wrote `Hello, RISC-V!` for _sifive_u_, I ignored its multi-core nature, resulting in duplicate and interleaved output.  
Refer to:  
- [QEMU - SiFive HiFive Unleashed (sifive_u)](https://qemu.readthedocs.io/en/latest/system/riscv/sifive_u.html)
- [SiFive - HiFive Unleashed](https://www.sifive.com/boards/hifive-unleashed)
- [SiFive FU540-C000 Manual v1p4](https://sifive.cdn.prismic.io/sifive/d3ed5cd0-6e74-46b2-a12d-72b06706513e_fu540-c000-manual-v1p4.pdf)

## Part 3. Interrupts and Process Scheduling

- [05: Interrupt Basics (TODO)](/05-Interrupt-Basics)  
- [06: Timer Interrupt (Code Completed)](/06-Timer-Interrupt)  
- [07: Simple Process Scheduling (Code Completed)](/07-Simple-Process-Scheduling)  
- [08: UART Interrupt (Partially Completed)](/08-UART-Interrupt)  

## Appendix
- [Appendix-00: Assembly and Linking Basics](/Appendix-00-Assembly-and-Linking/README.md)
