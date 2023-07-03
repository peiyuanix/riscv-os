# 04.1: Bare Metal Firmware for QEMU `sifive_u`

## Switch to `sifive_u`

**Switch to `sifive_u`, because `virt` is not well documented!**  

**Attention: _sifive_u_ has multiple cores!** When I first wrote `Hello, RISC-V!` for _sifive_u_, I ignored its multi-core nature, resulting in duplicate and interleaved output.  
Refer to:  
- [QEMU - SiFive HiFive Unleashed (sifive_u)](https://qemu.readthedocs.io/en/latest/system/riscv/sifive_u.html)
- [SiFive - HiFive Unleashed](https://www.sifive.com/boards/hifive-unleashed)
- [SiFive FU540-C000 Manual v1p4](https://sifive.cdn.prismic.io/sifive/d3ed5cd0-6e74-46b2-a12d-72b06706513e_fu540-c000-manual-v1p4.pdf)

## Bare Metal Echo Program

No more explanation. Just read the code.

Run with:  

```sh
make run
```
