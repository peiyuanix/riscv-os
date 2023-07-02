.global test_proc_0_entry
.global test_proc_0_stack_top

.text

test_proc_0_entry:
  li t0, 0x0
loop:
  addi t0, t0, 0x1
  j loop

test_proc_0_stack_bottom:
.rept (1 << 20)
  .byte 0
.endr
test_proc_0_stack_top:
  .byte 0
