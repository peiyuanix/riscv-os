source config.sh

qemu-system-riscv64 -M virt \
    -display none -serial stdio \
    -kernel ${BUILD_DIR}/linux-${KERNEL_VERSION}/arch/riscv/boot/Image