# 04.1: Bare Metal Firmware for QEMU `sifive_u`

## Switch to `sifive_u`

**Switch to `sifive_u`, because `virt` is not well documented!**  

**Attention: _sifive_u_ has multiple cores!** When I first wrote `Hello, RISC-V!` for _sifive_u_, I ignored its multi-core nature, resulting in duplicate and interleaved output.  
Refer to:  
- [QEMU - SiFive HiFive Unleashed (sifive_u)](https://qemu.readthedocs.io/en/latest/system/riscv/sifive_u.html)
- [SiFive - HiFive Unleashed](https://www.sifive.com/boards/hifive-unleashed)
- [SiFive FU540-C000 Manual v1p4](https://sifive.cdn.prismic.io/sifive/d3ed5cd0-6e74-46b2-a12d-72b06706513e_fu540-c000-manual-v1p4.pdf)

For multi-cluster machines, unfortunately gdb does not by default handle multiple inferiors, and so you have to explicitly connect to them. 
Refer to [QEMU Debugging multicore machines](https://qemu.readthedocs.io/en/latest/system/gdb.html#debugging-multicore-machines)

## Bare Metal Echo Program

The most important thing to know is: 

- sifive_u has multiple cores
- **hart-0** only supports `M/U-mode`, which means that it does **not support virtual memory**
- **hart-1** supports `M/S/U-mode`, which means it does **support virtual memory**

Thus, we only use hart-1 and leave the other cores idle.

Replace startup code with:
```asm
.text
firmware_entry:
  li t0, 0x1
  bne a0, t0, firmware_entry # loop if hartid is not 1
  li sp, 0x80200000 # setup stack pointer
  j firmware_main # jump to c entry
```

No more explanation. Just read the code.

Run with:  

```sh
make run
```

## GDB & QEMU: Debugging multicore machines

Refer to [QEMU Debugging multicore machines](https://qemu.readthedocs.io/en/latest/system/gdb.html#debugging-multicore-machines)

## References
- [QEMU - SiFive HiFive Unleashed (sifive_u)](https://qemu.readthedocs.io/en/latest/system/riscv/sifive_u.html)
- [SiFive - HiFive Unleashed](https://www.sifive.com/boards/hifive-unleashed)
- [SiFive FU540-C000 Manual v1p4](https://sifive.cdn.prismic.io/sifive/d3ed5cd0-6e74-46b2-a12d-72b06706513e_fu540-c000-manual-v1p4.pdf)
