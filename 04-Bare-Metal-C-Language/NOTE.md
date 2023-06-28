## 疑问

```c
 char str[] = "xxxxxx";
```

的字符数量一旦超过 6，程序就无法运行，似乎会导致 mcause 显示出异常。

测试情况：

str 不能是 char *，且不能字符数超过 6。

观察bin文件可以发现，一旦定义为 char *，或者长度超过 6，则会在bin文件中存储所定义的字符串，但是当以数组形式定义且长度小于等于6时，看不到定义的字符串，也许这时候直接以立即数形式存储了？？？？

**已验证**：通过 `riscv64-linux-gnu-gcc -S firmware.c -o bin/firmware.s` 将 C 源代码转换成汇编语言代码，查看汇编语言代码，即可验证上述现象。

**一种解决方案**：~~改用 elf~~，并在链接脚本中指定 `. = 0x80000000`，~~使 QEMU 直接加载 elf 格式的 firmware。或许是当str以数组形式定义且长度小于等于6时，产生的段比较复杂，objcopy产生的结果有问题？？？现在还不太清楚~~

猜测可能是对齐问题？

**新发现**：使用 ELF 不是必须的，重点是在链接脚本中指定 `. = 0x80000000`，且不要随便去控制 sections ，保持默认，无论是 bin 还是 elf，都可以正常输出长字符串！！！

**猜想**：通过设置、不设置 `. = 0x80000000` 生成了两个 binary 文件，对比发现，不同之处还不少。**猜测，可能是最终的文件依赖加载地址生成了绝对地址引用，因此正确设置加载地址才能保证可以跑！**


## 如何控制目标文件的浮点类型（不知道是传参还是指令生成方面的），比如 soft float

**mabi 的 f/d 后缀决定浮点处理方式**

参考资料：as man page

```
-march=ISA
           Select the base isa, as specified by ISA.  For example -march=rv32ima.  If this
           option and the architecture attributes aren't set, then assembler will check the
           default configure setting --with-arch=ISA.

-mabi=ABI
           Selects the ABI, which is either "ilp32" or "lp64", optionally followed by "f",
           "d", or "q" to indicate single-precision, double-precision, or quad-precision
           floating-point calling convention, or none to indicate the soft-float calling
           convention.  Also, "ilp32" can optionally be followed by "e" to indicate the RVE
           ABI, which is always soft-float.
```

[gcc RISC-V Options](https://gcc.gnu.org/onlinedocs/gcc-13.1.0/gcc/RISC-V-Options.html#RISC-V-Options-1)

```
-mabi=ABI-string

Specify integer and floating-point calling convention. ABI-string contains two parts: the size of integer types and the registers used for floating-point types. For example ‘-march=rv64ifd -mabi=lp64d’ means that ‘long’ and pointers are 64-bit (implicitly defining ‘int’ to be 32-bit), and that floating-point values up to 64 bits wide are passed in F registers. Contrast this with ‘-march=rv64ifd -mabi=lp64f’, which still allows the compiler to generate code that uses the F and D extensions but only allows floating-point values up to 32 bits long to be passed in registers; or ‘-march=rv64ifd -mabi=lp64’, in which no floating-point arguments will be passed in registers.

The default for this argument is system dependent, users who want a specific calling convention should specify one explicitly. The valid calling conventions are: ‘ilp32’, ‘ilp32f’, ‘ilp32d’, ‘lp64’, ‘lp64f’, and ‘lp64d’. Some calling conventions are impossible to implement on some ISAs: for example, ‘-march=rv32if -mabi=ilp32d’ is invalid because the ABI requires 64-bit values be passed in F registers, but F registers are only 32 bits wide. There is also the ‘ilp32e’ ABI that can only be used with the ‘rv32e’ architecture. This ABI is not well specified at present, and is subject to change.


-march=ISA-string

Generate code for given RISC-V ISA (e.g. ‘rv64im’). ISA strings must be lower-case. Examples include ‘rv64i’, ‘rv32g’, ‘rv32e’, and ‘rv32imaf’.

When -march= is not specified, use the setting from -mcpu.

If both -march and -mcpu= are not specified, the default for this argument is system dependent, users who want a specific architecture extensions should specify one explicitly.
```