#ifndef _UART_H
#define _UART_H

#include "riscv_types.h"
#include "riscv_asm.h"
#include <stdarg.h>

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

#define UART_IE_TXWM (1 << 0)
#define UART_IE_RXWM (1 << 1)

#define UART_REG(offset) (*(u32 *)(UART_BASE + offset))

static u8 *uart_base_addr = (u8 *)UART_BASE;

static inline void set_reg(u32 offset, u32 val)
{
  writeu32(uart_base_addr + offset, val);
}

static inline u32 get_reg(u32 offset)
{
  return readu32(uart_base_addr + offset);
}

static inline void uart_putc(u32 ch)
{
  while (get_reg(UART_TXDATA_OFFSET) & UART_TXFIFO_FULL)
    ;
  set_reg(UART_TXDATA_OFFSET, ch);
}

static inline u32 uart_getc()
{
  return get_reg(UART_RXDATA_OFFSET);
}

static inline void uart_print(char *str)
{
  while (*str)
  {
    uart_putc(*str++);
  }
}

static void uart_print_digit(unsigned long val, unsigned long base, bool uppercase)
{
  const char *digits = uppercase ? "0123456789ABCDEF" : "0123456789abcdef";

  if (val < base)
  {
    uart_putc(digits[val]);
  }
  else
  {
    uart_print_digit(val / base, base, uppercase);
    uart_putc(digits[val % base]);
  }
}

static inline void uart_print_int(int val, int base)
{
  if (val < 0)
  {
    uart_putc('-');
    val = -val;
  }
  uart_print_digit(val, base, false);
}

static inline void uart_print_uint(unsigned int val, int base)
{
  uart_print_digit(val, base, false);
}

static inline void uart_print_uint_upper(unsigned int val, int base)
{
  uart_print_digit(val, base, true);
}

static inline void uart_print_long(long val, int base)
{
  if (val < 0)
  {
    uart_putc('-');
    val = -val;
  }
  uart_print_digit(val, base, false);
}

static inline void uart_print_ulong(unsigned long val, int base)
{
  uart_print_digit(val, base, false);
}

static inline void uart_print_ulong_upper(unsigned long val, int base)
{
  uart_print_digit(val, base, true);
}

static inline void uart_printf(const char *format, ...)
{
  va_list args;
  va_start(args, format);

  while (*format)
  {
    if (*format == '%')
    {
      format++;
      switch (*format)
      {
      case 'c':
      {
        char c = (char)va_arg(args, unsigned int);
        uart_putc(c);
        break;
      }
      case 's':
      {
        char *str = va_arg(args, char *);
        uart_print(str);
        break;
      }
      case 'd':
      {
        int val = va_arg(args, int);
        uart_print_int(val, 10);
        break;
      }
      case 'u':
      {
        unsigned int val = va_arg(args, unsigned int);
        uart_print_uint(val, 10);
        break;
      }
      case 'x':
      {
        unsigned int val = va_arg(args, unsigned int);
        uart_print_uint(val, 16);
        break;
      }
      case 'X':
      {
        unsigned int val = va_arg(args, unsigned int);
        uart_print_uint_upper(val, 16);
        break;
      }
      case 'l':
      {
        format++;
        switch (*format)
        {
        case 'd':
        {
          long val = va_arg(args, long);
          uart_print_long(val, 10);
          break;
        }
        case 'u':
        {
          unsigned long val = va_arg(args, unsigned long);
          uart_print_ulong(val, 10);
          break;
        }
        case 'x':
        {
          unsigned long val = va_arg(args, unsigned long);
          uart_print_ulong(val, 16);
          break;
        }
        case 'X':
        {
          unsigned long val = va_arg(args, unsigned long);
          uart_print_ulong_upper(val, 16);
          break;
        }
        default:
          uart_putc(*format);
          break;
        }
        break;
      }
      default:
        uart_putc(*format);
        break;
      }
    }
    else
    {
      uart_putc(*format);
    }
    format++;
  }

  va_end(args);
}

static inline void uart_init()
{
  /* Configure baudrate */
  set_reg(UART_DIV_OFFSET, 0);

  /* Disable interrupts */
  set_reg(UART_IE_OFFSET, 0);

  /* Enable TX */
  set_reg(UART_TXCTRL_OFFSET, UART_TXCTRL_TXEN);

  /* Enable Rx */
  set_reg(UART_RXCTRL_OFFSET, UART_RXCTRL_RXEN);
}

static inline u32 _uart_ie()
{
  get_reg(UART_IE_OFFSET);
}

static inline void _uart_ie_write(u32 val)
{
  set_reg(UART_IE_OFFSET, val);
}

#endif