.section .text

.global _uart_init

UART_BASE = 0x10000000
UART_THR_OFFSET = 0

_uart_init:
  li gp, UART_BASE

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
