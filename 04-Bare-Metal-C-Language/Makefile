CROSS_COMPILE := riscv64-linux-gnu-
CC := ${CROSS_COMPILE}gcc
AS := ${CROSS_COMPILE}as
LD := ${CROSS_COMPILE}ld
OBJCOPY := ${CROSS_COMPILE}objcopy

bin/clang_env_init.bin: clang_env_init.s clang_env_init.ld
	${AS} clang_env_init.s -o bin/clang_env_init.o
	${CC} -c firmware.c -o bin/firmware.o
	${LD} -T clang_env_init.ld  bin/clang_env_init.o bin/firmware.o -o bin/firmware
	${OBJCOPY} -O binary -S bin/firmware bin/firmware.bin

run: bin/clang_env_init.bin
	qemu-system-riscv64 -machine virt -serial stdio -bios bin/firmware.bin

clean:
	rm -rf bin/

$(shell mkdir -p bin)