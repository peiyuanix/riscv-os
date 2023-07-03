# 04: Bare Metal Hello RISC-V - C Language Version

## Background

### C Program and Stack
The most important thing we need to know is that **C programs rely _Stack_ to run**.  

- For RISC-V, the stack pointer register is `sp` or `x2`. 
- When a C function is called, it allocates memory for its running by **decreasing** `sp`.  

The default `sp` at startup is `0x0`, and the memory space below `0x0` is of course illegal.  

Therefore, we must set a reasonable value for `sp`, so that we can jump from our startup code written in assembly to a C function.  

### C Program/RISC-V Calling Convention

Setuping stack pointer is enough for jumping from our assembly startup code to a C function.  
However, to call an assembly code snippet from a C function and return it, we need to learn how a C function passes parameters and receives a return value.  

**Just a reminder, we can ignore this for now in this tutorial.** For deatils, refer to [RISC-V Calling Conventions](https://github.com/riscv-non-isa/riscv-elf-psabi-doc/blob/master/riscv-cc.adoc).  

## Hello, RISC-V!

### Step.1 Setup Stack Pointer for C Program

Our firmware will be loaded to `0x80000000`, we can give `sp` a proper value for C program.  

```asm
.global _clang_env_init

.text
_clang_env_init:
li sp, 0x80200000 # give a proper memory address value to stack pointer
j _uart_init # jump to a C function

```

### Step.2 Write UART initialization code with **C Language**

```c
typedef char u8;
typedef short u16;
typedef int u32;
typedef long u64;

#define UART_BASE 0x10000000

#define UART_RBR_OFFSET		0	/* In:  Recieve Buffer Register */
#define UART_THR_OFFSET		0	/* Out: Transmitter Holding Register */
#define UART_DLL_OFFSET		0	/* Out: Divisor Latch Low */
#define UART_IER_OFFSET		1	/* I/O: Interrupt Enable Register */
#define UART_DLM_OFFSET		1	/* Out: Divisor Latch High */
#define UART_FCR_OFFSET		2	/* Out: FIFO Control Register */
#define UART_IIR_OFFSET		2	/* I/O: Interrupt Identification Register */
#define UART_LCR_OFFSET		3	/* Out: Line Control Register */
#define UART_MCR_OFFSET		4	/* Out: Modem Control Register */
#define UART_LSR_OFFSET		5	/* In:  Line Status Register */
#define UART_MSR_OFFSET		6	/* In:  Modem Status Register */
#define UART_SCR_OFFSET		7	/* I/O: Scratch Register */
#define UART_MDR1_OFFSET	8	/* I/O:  Mode Register */

#define PLATFORM_UART_INPUT_FREQ 10000000
#define PLATFORM_UART_BAUDRATE 115200

static u8 *uart_base_addr = (u8 *)UART_BASE;

static inline void writeb(u8 val, volatile void *addr)
{
	asm volatile("sb %0, 0(%1)" : : "r"(val), "r"(addr));
}

static inline u8 readb(const volatile void *addr)
{
	u8 val;
	asm volatile("lb %0, 0(%1)" : "=r"(val) : "r"(addr));
	return val;
}

static void set_reg(u32 offset, u32 val)
{
	writeb(val, uart_base_addr + offset);
}

static u32 get_reg(u32 offset)
{
	return readb(uart_base_addr + offset);
}

static void uart_putc(u8 ch) {
  set_reg(UART_THR_OFFSET, ch);
}

static void uart_print(char *str) {
  while (*str) {
    uart_putc(*str++);
  }
}

int _uart_init() {
  u16 bdiv = (PLATFORM_UART_INPUT_FREQ + 8 * PLATFORM_UART_BAUDRATE) / (16 * PLATFORM_UART_BAUDRATE);

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
  char *str = "Hello, RISC-V!\n";
  uart_print(str);

  while (1) {}
}
```

### Step.3 Build and Run

**IMPORTANT: Set Proper Location Counter in Linker Script!!!**

```
make run
```

## Read from console: echo

We can also read from console/uart, then print what user enters.  

The complete code is in [echo.c](echo.c). Run with `make echo`.  

```c
/* ... */
static int readble() {
	return get_reg(UART_LSR_OFFSET) & UART_LSR_DR;
}

/* ... */

int _uart_init() {
	/* ... */
	uart_print("Hello, RISC-V!\n");
	uart_print("echo > ");
	
	while (1) {
		if (readble()) {
			int ch = uart_getc();
			uart_putc(ch);
		}
	}
	/* ...... */
}
```

## References

- [RISC-V Calling Conventions](https://github.com/riscv-non-isa/riscv-elf-psabi-doc/blob/master/riscv-cc.adoc)
- [RISC-V Toolchain Conventions](https://github.com/riscv-non-isa/riscv-toolchain-conventions)
- [RISC-V ELF psABI Document](https://github.com/riscv-non-isa/riscv-elf-psabi-doc)
- [RISC-V Assembly Programmer's Manual](https://github.com/riscv-non-isa/riscv-asm-manual/blob/master/riscv-asm.md)