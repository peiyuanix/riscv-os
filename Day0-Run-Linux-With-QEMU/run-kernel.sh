BUILD_DIR="build"

qemu-system-riscv64 -M virt -m 2G \
    -display none -serial stdio \
    -kernel ${BUILD_DIR}/linux-5.12/arch/riscv/boot/Image