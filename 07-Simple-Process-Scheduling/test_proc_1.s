.global test_proc_1_entry
.global test_proc_1_stack_top

.text

test_proc_1_entry:
  li t0, 0x0
loop:
  addi t0, t0, 0x2
  j loop

test_proc_1_stack_bottom:
.rept (1 << 20)
  .byte 0
.endr
test_proc_1_stack_top:
  .byte 0
