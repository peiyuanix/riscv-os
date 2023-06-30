.global _clang_env_init

.text
_clang_env_init:
li sp, 0x80200000 # give a proper memory address value to stack pointer
j _uart_init # jump to a C function
