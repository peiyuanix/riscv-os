CROSS_COMPILE := riscv64-linux-gnu-
CC := ${CROSS_COMPILE}gcc
AS := ${CROSS_COMPILE}as
LD := ${CROSS_COMPILE}ld
OBJCOPY := ${CROSS_COMPILE}objcopy

bin/firmware.bin: clang_env_init.s firmware.c clang_env_init.ld
	${AS} clang_env_init.s -o bin/clang_env_init.o
	${CC} -c firmware.c -o bin/firmware.o
	${LD} -T clang_env_init.ld  bin/clang_env_init.o bin/firmware.o -o bin/firmware
	${OBJCOPY} -O binary -S bin/firmware bin/firmware.bin

run: bin/firmware.bin
	qemu-system-riscv64 -display none -machine virt -serial stdio -bios bin/firmware.bin

bin/echo.bin: clang_env_init.s firmware.c clang_env_init.ld
	${AS} clang_env_init.s -o bin/clang_env_init.o
	${CC} -c echo.c -o bin/echo.o
	${LD} -T clang_env_init.ld  bin/clang_env_init.o bin/echo.o -o bin/echo
	${OBJCOPY} -O binary -S bin/echo bin/echo.bin

echo: bin/echo.bin
	qemu-system-riscv64 -display none -machine virt -serial stdio -bios bin/echo.bin

clean:
	rm -rf bin/

$(shell mkdir -p bin)