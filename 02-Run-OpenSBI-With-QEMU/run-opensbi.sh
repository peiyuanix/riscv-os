source config.sh

# Method 1: Manually load OpenSBI flat binary image directly into the address space of the guest
qemu-system-riscv64 -M virt \
    -display none -serial stdio \
    -bios none \
    -device loader,file=${BUILD_DIR}/opensbi-${OPENSBI_VERSION}-rv-bin/share/opensbi/lp64/generic/firmware/fw_dynamic.bin,addr=0x80000000

# Method 2: Load OpenSBI flat binary image as bios
# qemu-system-riscv64 -M virt \
#     -display none -serial stdio \
#     -bios ${BUILD_DIR}/opensbi-${OPENSBI_VERSION}-rv-bin/share/opensbi/lp64/generic/firmware/fw_dynamic.bin

# Method 3: Load OpenSBI ELF as bios
# qemu-system-riscv64 -M virt \
#     -display none -serial stdio \
#     -bios ${BUILD_DIR}/opensbi-${OPENSBI_VERSION}-rv-bin/share/opensbi/lp64/generic/firmware/fw_dynamic.elf