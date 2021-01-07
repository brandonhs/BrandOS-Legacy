all: run

bin/kernel.bin: out/kernel-entry.o out/ports.o out/display.o out/kernel.o
	ld -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary --ignore-unresolved-symbol _GLOBAL_OFFSET_TABLE_

out/kernel-entry.o: kernel/kernel-entry.asm
	nasm $< -f elf -o $@

bin/boot.bin: boot/boot.asm
	nasm $< -f bin -o $@

out/kernel.o: kernel/kernel.c
	gcc -m32 -ffreestanding -c $< -o $@

out/display.o: drivers/display.c
	gcc -m32 -ffreestanding -c $< -o $@

out/ports.o: drivers/ports.c
	gcc -m32 -ffreestanding -c $< -o $@

bin/os.bin: bin/boot.bin bin/kernel.bin
	cat $^ > $@

run: bin/os.bin
	qemu-system-i386 -fda $<

