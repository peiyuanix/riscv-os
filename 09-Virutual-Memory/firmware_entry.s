.text
firmware_entry:
  bne a0, x0, firmware_entry # loop if hartid is not 0
  li sp, 0x80200000 # setup stack pointer
  j firmware_main # jump to c entry
