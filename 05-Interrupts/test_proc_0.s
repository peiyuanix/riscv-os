.global test_proc_0

.text

test_proc_0:
  li t0, 0x0
loop:
  addi t0, t0, 0x1
  j loop
