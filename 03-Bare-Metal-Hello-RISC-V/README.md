# 03: Bare Metal Hello RISC-V

## Background

### How does `qemu-system-riscv64 -machine virt` boot?

#### STEP.1 Power on and set pc to reset vector

Refer to [Source Code from QEMU](https://github.com/qemu/qemu/blob/v5.1.0/hw/riscv/virt.c#L504)

- QEMU power on
- `pc` is set to reset vector `0x1000`, where is the instructions from on-chip-rom

#### STEP.2 Run from on-chip-rom

Refer to [Source Code from QEMU](https://github.com/qemu/qemu/blob/v5.1.0/hw/riscv/boot.c#L224)

- Read `mhartid` from Control Status Register to `a0`
- Load value of `fdt_load_addr` to `a1`
- Jump to `start_addr`: `0x8000_0000`

**What is in `start_addr`**?

Refer to [Source Code from QEMU](https://github.com/qemu/qemu/blob/v5.1.0/hw/riscv/virt.c#L510), which loads bios firmware to `start_addr`.  

By default, bios firmware is OpenSBI. We can supply our own firmware by `-bios` option.  

In this Example, we load our bare metal program as firmware, to `start_addr` : `0x8000_0000`.  

#### STEP.3 bios, bootloader, kernel

Typically, OpenSBI loads a bootloader (probably U-Boot) as the next stage. Then, bootloader loads the kernel.  

```
On-Chip-Rom => OpenSBI => U-Boot => Kernel
```

Alternatively, OpenSBI can directly load the kernel.  

```
On-Chip-Rom => OpenSBI => Kernel
```

### Real-world RISC-V Boot Flow

Real-world RISC-V boot flow may be more diverse, refer to [An Introduction to RISC-V Boot Flow](https://riscv.org/wp-content/uploads/2019/12/Summit_bootflow.pdf).

## QEMU RISC-V *virt* Machine Memory Map

According to QEMU [source code](https://github.com/qemu/qemu/blob/v8.0.2/hw/riscv/virt.c#L77), the memory map of *virt* is as follows:  

```
static const MemMapEntry virt_memmap[] = {
    ...
    [VIRT_MROM] =         {     0x1000,        0xf000 }, /* On-Chip-ROM */
    ...
    [VIRT_UART0] =        { 0x10000000,         0x100 }, /* UART Device Registers Base Address */
    ...
    [VIRT_DRAM] =         { 0x80000000,           0x0 }, /* DRAM */
};
```
The point is: the UART device registers is mapped to `0x10000000`, we can operate UART by write/read uart registers.  

By reading [QEMU Manual - RISC-V Generic Virtual Platform](https://www.qemu.org/docs/master/system/riscv/virt.html), we can know that the UART device is a *NS16550 compatible UART*.  

However, I don't know how to configure the UART yet after reading datasheet [PC16550D Universal Asynchronous Receiver/Transmitter With FIFOs
](https://media.digikey.com/pdf/Data%20Sheets/Texas%20Instruments%20PDFs/PC16550D.pdf).  

Thanks for OpenSBI, which implements drivers for many kinds of RISC-V hardware, including *virt* of QEMU RISC-V. After searching *NS16550* keyword in OpenSBI source code for a while, I know that [**OpenSBI UART-8250 Driver**](https://github.com/riscv-software-src/opensbi/blob/master/lib/utils/serial/uart8250.c) serves for RISC-V *virt*'s UART.  

The core code for RISC-V *virt*'s UART initialization is as follows:  
```
int uart8250_init(unsigned long base, u32 in_freq, u32 baudrate, u32 reg_shift,
		  u32 reg_width, u32 reg_offset)
{
	u16 bdiv = 0;

	uart8250_base      = (volatile char *)base + reg_offset;
	uart8250_reg_shift = reg_shift;
	uart8250_reg_width = reg_width;
	uart8250_in_freq   = in_freq;
	uart8250_baudrate  = baudrate;

	if (uart8250_baudrate) {
		bdiv = (uart8250_in_freq + 8 * uart8250_baudrate) /
		       (16 * uart8250_baudrate);
	}

	/* Disable all interrupts */
	set_reg(UART_IER_OFFSET, 0x00);
	/* Enable DLAB */
	set_reg(UART_LCR_OFFSET, 0x80);

	if (bdiv) {
		/* Set divisor low byte */
		set_reg(UART_DLL_OFFSET, bdiv & 0xff);
		/* Set divisor high byte */
		set_reg(UART_DLM_OFFSET, (bdiv >> 8) & 0xff);
	}

	/* 8 bits, no parity, one stop bit */
	set_reg(UART_LCR_OFFSET, 0x03);
	/* Enable FIFO */
	set_reg(UART_FCR_OFFSET, 0x01);
	/* No modem control DTR RTS */
	set_reg(UART_MCR_OFFSET, 0x00);
	/* Clear line status */
	get_reg(UART_LSR_OFFSET);
	/* Read receive buffer */
	get_reg(UART_RBR_OFFSET);
	/* Set scratchpad */
	set_reg(UART_SCR_OFFSET, 0x00);

	sbi_console_set_device(&uart8250_console);

	return 0;
}
```

We can write our own UART initialization code according that.  

## Hello, RISC-V!

### Write UART initialization code

**For simplicity, we write the initialization code in RISC-V assembly so that we don't have to care about**  
- how assembly code interacts with C code
- how C code depends on the stack
- how C code passes and returns parameters
- and so on

```asm
.section .text

.global _uart_init

UART_BASE = 0x10000000

UART_RBR_OFFSET = 0
UART_THR_OFFSET = 0
UART_DLL_OFFSET = 0
UART_IER_OFFSET = 1
UART_DLM_OFFSET = 1
UART_FCR_OFFSET = 2
UART_IIR_OFFSET = 2
UART_LCR_OFFSET = 3
UART_MCR_OFFSET = 4
UART_LSR_OFFSET = 5
UART_MSR_OFFSET = 6
UART_SCR_OFFSET = 7
UART_MDR1_OFFSET = 8

PLATFORM_UART_ADDR = UART_BASE
PLATFORM_UART_INPUT_FREQ = 10000000
PLATFORM_UART_BAUDRATE = 115200

BDIV = (PLATFORM_UART_INPUT_FREQ + 8 * PLATFORM_UART_BAUDRATE) / (16 * PLATFORM_UART_BAUDRATE)

_uart_init:
  li gp, UART_BASE

  sb x0, UART_IER_OFFSET(gp)

  li t0, 0x80
  sb t0, UART_LCR_OFFSET(gp)

  li t0, BDIV & 0xFF
  sb t0, UART_DLL_OFFSET(gp)

  li t0, (BDIV >> 8) & 0xFF
  sb t0, UART_DLM_OFFSET(gp)

  li t0, 0x03
  sb t0, UART_LCR_OFFSET(gp)

  li t0, 0x01
  sb t0, UART_FCR_OFFSET(gp)

  sb x0, UART_MCR_OFFSET(gp)

  lb t0, UART_LSR_OFFSET(gp)

  lb t0, UART_RBR_OFFSET(gp)

  sb x0, UART_SCR_OFFSET(gp)


  # print
  li t0, 'H'
  sb t0, UART_THR_OFFSET(gp)

  li t0, 'e'
  sb t0, UART_THR_OFFSET(gp)

  li t0, 'l'
  sb t0, UART_THR_OFFSET(gp)

  li t0, 'l'
  sb t0, UART_THR_OFFSET(gp)

  li t0, 'o'
  sb t0, UART_THR_OFFSET(gp)

  li t0, ','
  sb t0, UART_THR_OFFSET(gp)

  li t0, ' '
  sb t0, UART_THR_OFFSET(gp)

  li t0, 'R'
  sb t0, UART_THR_OFFSET(gp)

  li t0, 'I'
  sb t0, UART_THR_OFFSET(gp)

  li t0, 'S'
  sb t0, UART_THR_OFFSET(gp)

  li t0, 'C'
  sb t0, UART_THR_OFFSET(gp)

  li t0, '-'
  sb t0, UART_THR_OFFSET(gp)

  li t0, 'V'
  sb t0, UART_THR_OFFSET(gp)

  li t0, '!'
  sb t0, UART_THR_OFFSET(gp)

  li t0, '\n'
  sb t0, UART_THR_OFFSET(gp)

loop:
  j loop

```

### Assemble and extract flat binary

To make it simple, we don't care the details of ELF file and how QEMU loads ELF file. We just extract the flat binary from ELF file and let QEMU loads the flat binary file.  

A flat binary file is just some machine instructions. The cpu knows how to interpret the instructions and execute them.  

#### Assemble assembly source code to ELF file

```
riscv64-linux-gnu-as firmware.s -o bin/firmware.o
```

#### Extract flat binary from the ELF file

```
riscv64-linux-gnu-objcopy -O binary -S bin/firmware.o bin/firmware.bin
```

**This differs slightly from what Makefile does, but it still works!**  


### Boot QEMU and load our own firmware as bios!

```
qemu-system-riscv64 -display none -machine virt -serial stdio -bios bin/firmware.bin
```

Then we can see `Hello, RISC-V!` being printed on the console!

## Possible Improvements

### Rewrite with C language
- Configure stack at the beginning so that C code can run
- Rewrite UART initialization code and printing code with C language

**Done:** [04: Bare Metal Hello RISC-V (C Language Version)](/04-Bare-Metal-C-Language)

### Respect OpenSBI: load our program as `-kernel`
OpenSBI is responsible for initializing a number of devices, including the UART.  

We can load our program as the next stage of OpenSBI, omit the initialization and use the UART device directly.  

**Some useful tips:**  

For *qemu-system-riscv64 -machine virt:*
- QEMU loads kernel to `0x80200000`  
- OpenSBI jumps to `0x80200000` after initialization
- QEMU accpets both ELF and flat binary as `-kernel`

## References
### About QEMU and *virt* Virtual Machine
- [QEMU Manual - Boot Image or Kernel specific](https://www.qemu.org/docs/master/system/invocation.html#hxtool-8)
- [QEMU Manual - RISC-V CPU firmware](https://www.qemu.org/docs/master/system/target-riscv.html#risc-v-cpu-firmware)
- [QEMU Manual - RISC-V Generic Virtual Platform](https://www.qemu.org/docs/master/system/riscv/virt.html)
- [QEMU RISC-V virt Machine Source Code](https://github.com/qemu/qemu/blob/master/hw/riscv/virt.c)
- [QEMU RISC-V Boot Helper Source Code](https://github.com/qemu/qemu/blob/master/hw/riscv/boot.c)
- [RISC-V from scratch 2: Hardware layouts, linker scripts, and C runtimes](https://twilco.github.io/riscv-from-scratch/2019/04/27/riscv-from-scratch-2.html)

### About RISC-V Boot Flow
- [An Introduction to RISC-V Boot Flow](https://riscv.org/wp-content/uploads/2019/12/Summit_bootflow.pdf)
- [OpenSBI Platform Firmwares](https://github.com/riscv-software-src/opensbi/blob/master/docs/firmware/fw.md)
- [QEMU RISC-V virt 平台分析](https://juejin.cn/post/6891922292075397127)

### About RISC-V Architecture
- [The RISC-V Reader: An Open Architecture Atlas](http://riscvbook.com/)
- [RISC-V Assembly Programmer's Manual](https://github.com/riscv-non-isa/riscv-asm-manual/blob/master/riscv-asm.md)
- [RISC-V ELF psABI Document](https://github.com/riscv-non-isa/riscv-elf-psabi-doc)

### About *virt*'s NS16550 UART Driver
- [**OpenSBI UART-8250 Driver - Compatible with NS16550 of RISC-V virt**](https://github.com/riscv-software-src/opensbi/blob/master/lib/utils/serial/uart8250.c)
- [PC16550D Universal Asynchronous Receiver/Transmitter With FIFOs
](https://media.digikey.com/pdf/Data%20Sheets/Texas%20Instruments%20PDFs/PC16550D.pdf)

### Releated Toolchains
- [as - The GNU assembler](https://ftp.gnu.org/old-gnu/Manuals/gas-2.9.1/html_node/as_toc.html)
- [ld - The GNU Linker: Command Language](https://ftp.gnu.org/old-gnu/Manuals/ld-2.9.1/html_chapter/ld_3.html#SEC5)
- [objcopy - copy and translate object files](https://ftp.gnu.org/old-gnu/Manuals/binutils-2.12/html_node/binutils_5.html)