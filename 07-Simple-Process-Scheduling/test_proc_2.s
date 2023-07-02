.global test_proc_2_entry
.global test_proc_2_stack_top

.text

test_proc_2_entry:
  li t0, 0x0
loop:
  addi t0, t0, 0x3
  j loop

test_proc_2_stack_bottom:
.rept (1 << 20)
  .byte 0
.endr
test_proc_2_stack_top:
  .byte 0
