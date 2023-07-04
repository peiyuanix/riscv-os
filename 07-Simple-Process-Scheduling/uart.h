#ifndef _UART_H
#define _UART_H

#include "riscv_arch.h"
#include "riscv_asm.h"
#include <stdarg.h>

#define UART_BASE 0x10000000

#define UART_RBR_OFFSET 0  /* In:  Recieve Buffer Register */
#define UART_THR_OFFSET 0  /* Out: Transmitter Holding Register */
#define UART_DLL_OFFSET 0  /* Out: Divisor Latch Low */
#define UART_IER_OFFSET 1  /* I/O: Interrupt Enable Register */
#define UART_DLM_OFFSET 1  /* Out: Divisor Latch High */
#define UART_FCR_OFFSET 2  /* Out: FIFO Control Register */
#define UART_IIR_OFFSET 2  /* I/O: Interrupt Identification Register */
#define UART_LCR_OFFSET 3  /* Out: Line Control Register */
#define UART_MCR_OFFSET 4  /* Out: Modem Control Register */
#define UART_LSR_OFFSET 5  /* In:  Line Status Register */
#define UART_MSR_OFFSET 6  /* In:  Modem Status Register */
#define UART_SCR_OFFSET 7  /* I/O: Scratch Register */
#define UART_MDR1_OFFSET 8 /* I/O:  Mode Register */

#define PLATFORM_UART_INPUT_FREQ 10000000
#define PLATFORM_UART_BAUDRATE 115200

static u8 *uart_base_addr = (u8 *)UART_BASE;

static void set_reg(u32 offset, u32 val)
{
  writeu8(uart_base_addr + offset, val);
}

static u32 get_reg(u32 offset)
{
  return readu8(uart_base_addr + offset);
}

static void uart_putc(u8 ch)
{
  set_reg(UART_THR_OFFSET, ch);
}

static void uart_print(char *str)
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
  u16 bdiv = (PLATFORM_UART_INPUT_FREQ + 8 * PLATFORM_UART_BAUDRATE) / (16 * PLATFORM_UART_BAUDRATE);

  /* Disable all interrupts */
  set_reg(UART_IER_OFFSET, 0x00);
  /* Enable DLAB */
  set_reg(UART_LCR_OFFSET, 0x80);

  if (bdiv)
  {
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
}

#endif