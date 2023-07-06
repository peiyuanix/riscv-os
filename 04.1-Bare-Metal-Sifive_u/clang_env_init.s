.global _clang_env_init

.text
_clang_env_init:
  li t1, 0x1
  bne a0, t1, _clang_env_init # loop if hartid is not 1
  li sp, 0x80200000 # setup stack pointer
  j firmware_main # jump to c entry
