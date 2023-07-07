.global firmware_entry

.text
firmware_entry:
  bne a0, x0, firmware_entry # loop if hartid is not 0
  la t1, kernel_stack_top
  ld sp, 0(t1) # setup stack pointer
  j firmware_main # jump to c entry
