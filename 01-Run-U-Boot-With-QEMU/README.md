# 01: Run U-Boot With QEMU RISC-V

## Build U-Boot
Download and build U-Boot with [build-uboot.sh](build-uboot.sh)  

```sh
bash build-uboot.sh
```

## Run U-Boot With QEMU

Boot just built kernel with QEMU: [run-uboot.sh](run-uboot.sh)  

```sh
bash run-uboot.sh
```

Then you can see U-Boot boots.

**NOTICE**: The output of U-Boot `u-boot.bin` is a flat binary.