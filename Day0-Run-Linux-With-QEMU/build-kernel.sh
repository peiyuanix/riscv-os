BUILD_DIR="build"

mkdir -p ${BUILD_DIR}

pushd ${BUILD_DIR}

curl -LOJ https://github.com/torvalds/linux/archive/refs/tags/v5.12.tar.gz
tar -xf linux-5.12.tar.gz

cd linux-5.12
export ARCH=riscv
export CROSS_COMPILE=riscv64-linux-gnu-
make defconfig
make -j 8

popd

