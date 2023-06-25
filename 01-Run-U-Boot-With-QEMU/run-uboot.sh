source config.sh

qemu-system-riscv64 -M virt \
    -display none -serial stdio \
    -kernel ${BUILD_DIR}/u-boot-${UBOOT_VERSION}/u-boot.bin