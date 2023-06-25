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

**NOTE**: `-kernel` parameter of QEMU accepts both flat binary and elf file.  
- `u-boot.bin`: flat binary  
  ```
  $ file build/u-boot-2021.04/u-boot.bin 
  build/u-boot-2021.04/u-boot.bin: data
  ```
- `u-boot`: ELF   
  ```
  $ file build/u-boot-2021.04/u-boot
  build/u-boot-2021.04/u-boot: ELF 64-bit LSB executable, UCB RISC-V, version 1 (SYSV), dynamically linked, with debug_info, not stripped
  ```
