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

#define UART_LSR_FIFOE		0x80	/* Fifo error */
#define UART_LSR_TEMT		0x40	/* Transmitter empty */
#define UART_LSR_THRE		0x20	/* Transmit-hold-register empty */
#define UART_LSR_BI		0x10	/* Break interrupt indicator */
#define UART_LSR_FE		0x08	/* Frame error indicator */
#define UART_LSR_PE		0x04	/* Parity error indicator */
#define UART_LSR_OE		0x02	/* Overrun error indicator */
#define UART_LSR_DR		0x01	/* Receiver data ready */
#define UART_LSR_BRK_ERROR_BITS	0x1E	/* BI, FE, PE, OE bits */

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

static int writable() {
	return (get_reg(UART_LSR_OFFSET) & UART_LSR_THRE) == 0;
}

static int readble() {
	return get_reg(UART_LSR_OFFSET) & UART_LSR_DR;
}

static int uart_getc() {
  return get_reg(UART_RBR_OFFSET);
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

  uart_print("Hello, RISC-V!\n");
  uart_print("echo > ");

  while (1) {
		if (readble()) {
			int ch = uart_getc();
			uart_putc(ch);
		}
	}
}