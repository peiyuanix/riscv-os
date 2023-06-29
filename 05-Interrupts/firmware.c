typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long u64;

#define UART_BASE 0x10010000

#define UART_TXDATA_OFFSET 0x00
#define UART_RXDATA_OFFSET 0x04
#define UART_TXCTRL_OFFSET 0x08
#define UART_RXCTRL_OFFSET 0x0c
#define UART_IE_OFFSET 0x10
#define UART_IP_OFFSET 0x14
#define UART_DIV_OFFSET 0x18

#define UART_TXFIFO_FULL 0x80000000
#define UART_RXFIFO_EMPTY 0x80000000
#define UART_RXFIFO_DATA 0x000000ff
#define UART_TXCTRL_TXEN 0x1
#define UART_RXCTRL_RXEN 0x1

#define PLATFORM_UART_INPUT_FREQ 10000000
#define PLATFORM_UART_BAUDRATE 115200

#define UART_REG(offset) (*(u32 *)(UART_BASE + offset))

static u8 *uart_base_addr = (u8 *)UART_BASE;

static inline void write4b(u32 val, volatile void *addr)
{
  asm volatile("sw %0, 0(%1)"
               :
               : "r"(val), "r"(addr));
}

static inline u32 read4b(const volatile void *addr)
{
  u32 val;
  asm volatile("lw %0, 0(%1)"
               : "=r"(val)
               : "r"(addr));
  return val;
}

static void set_reg(u32 offset, u32 val)
{
  write4b(val, uart_base_addr + offset);
}

static u32 get_reg(u32 offset)
{
  return read4b(uart_base_addr + offset);
}

static void uart_putc(u32 ch)
{
  while (get_reg(UART_TXDATA_OFFSET) & UART_TXFIFO_FULL)
    ;
  set_reg(UART_TXDATA_OFFSET, ch);
}

static u32 uart_getc()
{
  return get_reg(UART_RXDATA_OFFSET);
}

static void uart_print(char *str)
{
  while (*str)
  {
    uart_putc(*str++);
  }
}

int _uart_init()
{
  /* Configure baudrate */
  set_reg(UART_DIV_OFFSET, 0);

  /* Disable interrupts */
  set_reg(UART_IE_OFFSET, 0);

  /* Enable TX */
  set_reg(UART_TXCTRL_OFFSET, UART_TXCTRL_TXEN);

  /* Enable Rx */
  set_reg(UART_RXCTRL_OFFSET, UART_RXCTRL_RXEN);

  uart_print("Hello, RISC-V!\n");

  uart_print("echo> ");

  for (;;)
  {
    u32 data = uart_getc();
    if (!(data & UART_RXFIFO_EMPTY))
    {
      uart_putc(data & UART_RXFIFO_DATA);
    }
  }
}