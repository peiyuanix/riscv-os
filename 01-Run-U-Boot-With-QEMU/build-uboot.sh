source config.sh

mkdir -p ${BUILD_DIR}

cd ${BUILD_DIR}

curl -LOJ https://github.com/u-boot/u-boot/archive/refs/tags/v${UBOOT_VERSION}.tar.gz

tar -xf u-boot-${UBOOT_VERSION}.tar.gz

cd u-boot-${UBOOT_VERSION}
export CROSS_COMPILE=riscv64-linux-gnu-
make qemu-riscv64_smode_defconfig
make -j 8
