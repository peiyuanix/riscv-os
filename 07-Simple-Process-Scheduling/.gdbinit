set architecture riscv:rv64
set disassemble-next-line on
target extended-remote localhost:1234
add-inferior
inferior 2
attach 2
