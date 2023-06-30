## Compilation and Linking Basics
### Related file types and concepts  
- machine instruction  
- assembly source code file  
- relocatable object file
- executable file

### Compilation and linking workflow  
- The CPU can only decode and execute _machine instructions_.  
- An _assembly source code file_ consists of assembly instructions, which are symbolic representations of machine instructions.  
- The assembler can translate an _assembly source file_ into a _relocatable file_.  
- A relocatable file contains machine instructions and some meta information.  
- A relocatable file can't be loaded and executed directly, because it may reference some symbols whose address values are not known yet.  
- Multiple _relocatable flles_ can be linked to resolve unknown symbols and form _an executable file_.  
- An executable file contains machine instructions to be executed, and its meta information specifies the memory address where the program should be loaded.

**Why does a symbol with an unknown address value exist?**  
Take the following assembly source code file `test.s` as an example.  
```asm
.text

hello_string:
.string "Hello, RISC-V!"

la t0, hello_string
# Suppose here is a code snippet 
# that prints the string starting at address value in t0

```

We can assemble it to a relocatable file with `riscv64-linux-gnu-as`.  

```bash
riscv64-linux-gnu-as test.s -o test.o
```

For details, refer to [Executable and Linkable Format (ELF)](http://www.skyfree.org/linux/references/ELF_Format.pdf)