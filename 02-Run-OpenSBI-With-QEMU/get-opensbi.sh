source config.sh

mkdir -p ${BUILD_DIR}

cd ${BUILD_DIR}

curl -LOJ https://github.com/riscv-software-src/opensbi/releases/download/v${OPENSBI_VERSION}/opensbi-${OPENSBI_VERSION}-rv-bin.tar.xz

tar -xf opensbi-${OPENSBI_VERSION}-rv-bin.tar.xz
