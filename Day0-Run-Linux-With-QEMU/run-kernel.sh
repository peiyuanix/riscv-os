source config.sh

qemu-system-riscv64 -M virt -m 2G \
    -display none -serial stdio \
    -kernel ${BUILD_DIR}/linux-${KERNEL_VERSION}/arch/riscv/boot/Image