.text

/* load a immediate value to t0 */
lui t0, %hi(0x12345678)        /* higher 20 bits */
addi t0, t0, %lo(0x12345678)   /* lower 12 bits  */

/* load a symbol value to t0 */
lui t0, %hi(hello_string)
addi t0, t0, %lo(hello_string)

/* define a string */
hello_string:
.string "Hello, RISC-V!"
