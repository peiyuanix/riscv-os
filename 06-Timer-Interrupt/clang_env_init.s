.global _clang_env_init

.text
_clang_env_init:
  bne a0, x0, _clang_env_init # loop if hartid is not 0
  li sp, 0x80200000 # setup stack pointer
  j firmware_main # jump to c entry
