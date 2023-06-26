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

UART_LSR_FIFOE = 0x80
UART_LSR_TEMT = 0x40
UART_LSR_THRE = 0x20
UART_LSR_BI = 0x10
UART_LSR_FE = 0x08
UART_LSR_PE = 0x04
UART_LSR_OE = 0x02
UART_LSR_DR = 0x01
UART_LSR_BRK_ERROR_BITS = 0x1E

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
