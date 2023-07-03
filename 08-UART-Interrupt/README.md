# 05: Interrupts

## Switch to `sifive_u`, because `virt` is not well documented!

Refer to:  
- [QEMU - SiFive HiFive Unleashed (sifive_u)](https://qemu.readthedocs.io/en/latest/system/riscv/sifive_u.html)
- [SiFive - HiFive Unleashed](https://www.sifive.com/boards/hifive-unleashed)
- [SiFive FU540-C000 Manual v1p4](https://sifive.cdn.prismic.io/sifive/d3ed5cd0-6e74-46b2-a12d-72b06706513e_fu540-c000-manual-v1p4.pdf)

**Attention: _sifive_u_ has multiple cores!** When I first wrote `Hello, RISC-V!` for _sifive_u_, I ignored its multi-core nature, resulting in duplicate and interleaved output.  

## RISC-V Interrupt Basics
### Related Privilege Registers
### CLINT - Core Local Interrupt
### PLIC - Platform Level Interrupt Controller

## Timer Interrupt-based Process Scheduling

```sh
make run
```

## UART0 Receiver Interrupt
todo

## References

- [QEMU - SiFive HiFive Unleashed (sifive_u)](https://qemu.readthedocs.io/en/latest/system/riscv/sifive_u.html)
- [SiFive - HiFive Unleashed](https://www.sifive.com/boards/hifive-unleashed)
- [SiFive FU540-C000 Manual v1p4](https://sifive.cdn.prismic.io/sifive/d3ed5cd0-6e74-46b2-a12d-72b06706513e_fu540-c000-manual-v1p4.pdf)
- [Github - freedom-u540-c000-bootloader](https://github.com/sifive/freedom-u540-c000-bootloader/tree/24f612fe7ab54f213214e0e7e1f56bf839cb3bb8)
- [RISC-V Platform-Level Interrupt Controller Specification](https://github.com/riscv/riscv-plic-spec/blob/master/riscv-plic.adoc#interrupt-targets-and-hart-contexts)