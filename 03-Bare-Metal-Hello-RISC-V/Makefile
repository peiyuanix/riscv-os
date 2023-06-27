CROSS_COMPILE := riscv64-linux-gnu-
AS := ${CROSS_COMPILE}as
LD := ${CROSS_COMPILE}ld
OBJCOPY := ${CROSS_COMPILE}objcopy

bin/firmware.bin: firmware.s firmware.ld
	${AS} firmware.s -o bin/firmware.o
	${LD} -T firmware.ld  bin/firmware.o -o bin/firmware
	${OBJCOPY} -O binary -S bin/firmware bin/firmware.bin

run: bin/firmware.bin
	qemu-system-riscv64 -display none -machine virt -serial stdio -bios bin/firmware.bin

clean:
	rm -rf bin/

$(shell mkdir -p bin)