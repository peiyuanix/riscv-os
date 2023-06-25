## Something I don't understand yet

### Linux kernel is not a ELF file

The output of Linux kernel `arch/riscv/boot/Image` is a EFI file instead of a ELF file? I expect to get a kernel in ELF format.  

Some references: 

- [The EFI Boot Stub](https://docs.kernel.org/admin-guide/efi-stub.html)
- [RISC-V Linux kernel image format standardization](https://groups.google.com/a/groups.riscv.org/g/sw-dev/c/_xCn1SZn1Gg?pli=1)

### What formats of system images are supported by QEMU's `-kernel` parameter?

- Linux kernel in EFI foramt  
- Maybe some other formats?