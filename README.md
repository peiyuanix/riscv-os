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

**~~Switch to `sifive_u`, because `virt` is not well documented!~~**

- ~~[04.1: Bare Metal Hello Sifive_u](/04.1-Bare-Metal-Sifive_u)~~

After some attempts, I found that I had to revert back to `virt` because `sifive_u` doesn't support supervisor mode, which means it doesn't support virtual memory.  

## Part 3. Interrupts and Process Scheduling

- [05: Interrupt Basics (TODO)](/05-Interrupt-Basics)  
- [06: Timer Interrupt (Code Completed)](/06-Timer-Interrupt)  
- [07: Timer Interrupt-based Process Scheduling (Code Completed)](/07-Simple-Process-Scheduling)  
- [08: UART Interrupt (Partially Completed)](/08-UART-Interrupt)  

## Appendix
- [Appendix-00: Assembly and Linking Basics](/Appendix-00-Assembly-and-Linking/README.md)
