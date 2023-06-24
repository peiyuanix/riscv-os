# Day0: Run Linux Kernel With QEMU RISC-V

## Build Linux Kernel
Download and build Linux kernel with [build-kernel.sh](build-kernel.sh)

## Boot Linux Kernel With QEMU

Boot just built kernel with QEMU: [run-kernel.sh](run-kernel.sh)

You can see that Linux kernel boots then panics, because there is no rootfs provided.  

**THE POINT**: QEMU boots linux kernel successfully!

Now, you know that QEMU can boot Linux kernel. We can go ahead and write our own kernel!

## (Optional) NO PANIC - Minimal Rootfs

The panic looks unpleasant, doesn't it? We can provide a rootfs image for QEMU to get a usable minimal linux environment.

Build a minimal rootfs with busybox: [build-rootfs.sh](build-rootfs.sh)

Boot kernel and rootfs with QEMU: [run-kernel-with-rootfs.sh](run-kernel-with-rootfs.sh)