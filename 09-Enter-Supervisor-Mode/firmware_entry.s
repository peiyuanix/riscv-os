.global firmware_entry

.text
firmware_entry:
  li t0, 0x1
  bne a0, t0, firmware_entry # loop if hartid is not 1
  la t1, kernel_stack_top
  ld sp, 0(t1) # setup stack pointer
  j firmware_main # jump to c entry
