CROSS_COMPILE := riscv64-linux-gnu-
CC := ${CROSS_COMPILE}gcc
AS := ${CROSS_COMPILE}as
LD := ${CROSS_COMPILE}ld
OBJCOPY := ${CROSS_COMPILE}objcopy

ASM_SRC := firmware_entry.s mtrap_entry.s strap_entry.s
CLANG_SRC := firmware.c mtrap_handler.c strap_handler.c proc.c kstring.c test_processes.c
HEADERS := riscv_arch.h riscv_asm.h uart.h timer.h riscv_priv.h \
					proc.h kstring.h riscv_cpu.h

OBJECTS = $(addprefix bin/,$(ASM_SRC:.s=.asmo))
OBJECTS += $(addprefix bin/,$(CLANG_SRC:.c=.clango))

all: bin/firmware.bin

bin/firmware.bin: ${OBJECTS} ${HEADERS} firmware.ld
	${LD} --no-relax -T firmware.ld ${OBJECTS} -o bin/firmware
	${OBJCOPY} -O binary -S bin/firmware bin/firmware.bin

bin/%.asmo: %.s
	${AS} -g $< -o $@

bin/%.clango: %.c ${HEADERS}
	${CC} -ffreestanding -c -O0 -g $< -o $@

run: bin/firmware.bin
	qemu-system-riscv64 -machine virt -smp 1 -m 2G -serial stdio -bios bin/firmware.bin -s -display none

debug: bin/firmware.bin
	qemu-system-riscv64 -machine virt -smp 1 -m 2G -serial stdio -bios bin/firmware.bin -s -S

clean:
	rm -rf bin/

$(shell mkdir -p bin)