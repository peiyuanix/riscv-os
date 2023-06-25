# Day0: Run Linux Kernel With QEMU RISC-V

## Build Linux Kernel
Download and build Linux kernel with [build-kernel.sh](build-kernel.sh)  

```sh
bash build-kernel.sh
```

## Boot Linux Kernel With QEMU

Boot just built kernel with QEMU: [run-kernel.sh](run-kernel.sh)  

```sh
bash run-kernel.sh
```

You can see that Linux kernel boots then panics, because there is no rootfs provided.  

**THE POINT**: QEMU boots linux kernel successfully!

Now, you know that QEMU can boot Linux kernel. We can go ahead and write our own kernel!

## (Optional) NO PANIC - Minimal Rootfs

The panic looks unpleasant, doesn't it? We can provide a rootfs image for QEMU to get a minimal working Linux environment.


### [What is initramfs?](https://www.kernel.org/doc/Documentation/filesystems/ramfs-rootfs-initramfs.txt)

```
All 2.6 Linux kernels contain a gzipped "cpio" format archive, which is
extracted into rootfs when the kernel boots up.  After extracting, the kernel
checks to see if rootfs contains a file "init", and if so it executes it as PID
1.  If found, this init process is responsible for bringing the system the
rest of the way up, including locating and mounting the real root device (if
any).  If rootfs does not contain an init program after the embedded cpio
archive is extracted into it, the kernel will fall through to the older code
to locate and mount a root partition, then exec some variant of /sbin/init
out of that.
```

### Build initramfs and run it with Linux kernel

#### STEP 1. Build linux kernel as before  

  ```sh
  bash build-kernel.sh
  ```

#### STEP 2. Build a minimal rootfs with busybox: [build-rootfs.sh](build-rootfs.sh)  

  ```sh
  bash build-rootfs.sh
  ```

  The above rootfs contains the common Linux folders and utils, and mounts the proc, sysfs and tmpfs virtual filesystems to construct a working Linux rootfs. However, this rootfs is still too complex for understanding Linux kernel boot, we can build an truly minimal initramfs containing only the necessary `/init` with [build-minimal-rootfs.sh](build-minimal-rootfs.sh)

#### STEP 3. Boot kernel and rootfs with QEMU: [run-kernel-with-rootfs.sh](run-kernel-with-rootfs.sh)  

  ```sh
  bash run-kernel-with-rootfs.sh
  ```
