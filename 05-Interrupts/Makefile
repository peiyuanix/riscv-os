CROSS_COMPILE := riscv64-linux-gnu-
CC := ${CROSS_COMPILE}gcc
AS := ${CROSS_COMPILE}as
LD := ${CROSS_COMPILE}ld
OBJCOPY := ${CROSS_COMPILE}objcopy

bin/firmware.bin: clang_env_init.s firmware.c trap.s riscv_asm.h riscv_types.h uart.h clang_env_init.ld
	${AS} clang_env_init.s -g -o bin/clang_env_init.o
	${AS} trap.s -g -o bin/trap.o
	${CC} -c firmware.c -O0 -g -o bin/firmware.o
	${LD} -T clang_env_init.ld bin/clang_env_init.o bin/trap.o bin/firmware.o -o bin/firmware
	${OBJCOPY} -O binary -S bin/firmware bin/firmware.bin

run: bin/firmware.bin
	qemu-system-riscv64 -display none -machine sifive_u -smp 2 -m 2G -serial stdio -bios bin/firmware.bin -s

debug: bin/firmware.bin
	qemu-system-riscv64 -machine sifive_u -serial stdio -bios bin/firmware.bin -s -S -display none

clean:
	rm -rf bin/

$(shell mkdir -p bin)