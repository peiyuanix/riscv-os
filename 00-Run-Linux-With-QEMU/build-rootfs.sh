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

mkdir -p bin dev proc sys
pushd bin
    cp ../../busybox ./

    for prog in $(busybox --list); do
        ln -s /bin/busybox ./$prog
    done
popd # bin

cat <<EOF > init
#!/bin/sh
mount -t sysfs sysfs /sys
mount -t proc proc /proc
mount -t devtmpfs udev /dev
sysctl -w kernel.printk="2 4 1 7"
clear
/bin/sh
poweroff -f
EOF

chmod a+x init

find . | cpio -o -H newc > ../rootfs.cpio
