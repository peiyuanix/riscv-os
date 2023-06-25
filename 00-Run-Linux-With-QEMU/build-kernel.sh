source config.sh

mkdir -p ${BUILD_DIR}

cd ${BUILD_DIR}

curl -LOJ https://github.com/torvalds/linux/archive/refs/tags/v${KERNEL_VERSION}.tar.gz
tar -xf linux-${KERNEL_VERSION}.tar.gz

cd linux-${KERNEL_VERSION}
export ARCH=riscv
export CROSS_COMPILE=riscv64-linux-gnu-
make defconfig
make -j $(nproc)
