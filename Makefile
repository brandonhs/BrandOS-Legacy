C_SOURCES = $(wildcard src/kernel/cli/*.c src/kernel/*.c src/drivers/*.c src/cpu/*.c)
HEADERS = $(wildcard src/kernel/cli/*.h src/kernel/*.h src/drivers/*.h src/cpu/*.h)
OBJ = ${C_SOURCES:.c=.o src/cpu/interrupt.o} 

CC = i386-elf-gcc
GDB = i386-elf-gdb
CFLAGS = -g 

os-image.bin: src/boot/boot.bin src/kernel/kernel.bin
	cat $^ > os-image.bin

src/kernel/kernel.bin: src/kernel/kernel-entry.o ${OBJ}
	i386-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

kernel.elf: boot/kernel-entry.o ${OBJ}
	i386-elf-ld -o $@ -Ttext 0x1000 $^ 

run: os-image.bin
	qemu-system-i386 -fda os-image.bin

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -ffreestanding -c $< -o $@

src/kernel/kernel-entry.o: src/kernel/kernel-entry.asm
	nasm $< -f elf -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	rm -rf *.bin *.dis *.o os-image.bin *.elf
	rm -rf src/kernel/*.o src/kernel/*.bin src/boot/*.bin src/drivers/*.o src/boot/*.o src/cpu/*.o
