CROSS_COMPILE := riscv64-linux-gnu-
AS := ${CROSS_COMPILE}as
LD := ${CROSS_COMPILE}ld
OBJCOPY := ${CROSS_COMPILE}objcopy

run: bin/bootloader.bin
	qemu-system-riscv64 -display none -machine virt -serial stdio -bios bin/bootloader.bin

bin/bootloader.bin: bootloader.s bootloader.ld
	${AS} bootloader.s -o bin/bootloader.o
	${LD} -T bootloader.ld  bin/bootloader.o -o bin/bootloader
	${OBJCOPY} -O binary -S bin/bootloader bin/bootloader.bin

clean:
	rm -rf bin/

$(shell mkdir -p bin)