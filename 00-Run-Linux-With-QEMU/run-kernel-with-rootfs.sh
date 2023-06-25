source config.sh

qemu-system-riscv64 -machine virt \
    -display none -serial stdio \
    -kernel ${BUILD_DIR}/linux-${KERNEL_VERSION}/arch/riscv/boot/Image \
    -initrd ${BUILD_DIR}/busybox-${BUSYBOX_VERSION}/rootfs.cpio