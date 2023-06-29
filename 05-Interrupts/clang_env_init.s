.global _clang_env_init

.text
_clang_env_init:
  li sp, 0x80200000
  j _uart_init