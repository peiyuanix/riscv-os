source config.sh

mkdir -p ${BUILD_DIR}

cd ${BUILD_DIR}

curl -LOJ https://busybox.net/downloads/busybox-${BUSYBOX_VERSION}.tar.bz2
tar -xf busybox-${BUSYBOX_VERSION}.tar.bz2

cd busybox-${BUSYBOX_VERSION}
export CROSS_COMPILE=riscv64-linux-gnu-
make defconfig
sed 's/^.*CONFIG_STATIC[^_].*$/CONFIG_STATIC=y/g' -i .config
make -j $(nproc)

# initrd
mkdir -p initrd
cd initrd

cp ../busybox .

cat <<EOF > init
#!/busybox sh
/busybox sh
/busybox poweroff -f
EOF

chmod a+x init

find . | cpio -o -H newc > ../rootfs.cpio
