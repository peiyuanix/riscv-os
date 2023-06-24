# Day0: Run Linux Kernel With QEMU RISC-V

## Build Linux Kernel
Download and build Linux kernel with [build-kernel.sh](build-kernel.sh).

## Boot Linux Kernel With QEMU

You can see that Linux kernel boots then panics, because there is no rootfs provided.  

**THE POINT**: QEMU boots linux kernel successfully!

```
BUILD_DIR="build"

qemu-system-riscv64 -M virt -m 2G \
    -display none -serial stdio \
    -kernel ${BUILD_DIR}/linux-5.12/arch/riscv/boot/Image
```