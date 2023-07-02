.global test_proc_1

.text

test_proc_1:
  li t0, 0x0
loop:
  addi t0, t0, 0x2
  j loop
