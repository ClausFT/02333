bochs/boot.iso : objects/kernel.stripped bochs/grub.cfg | objects
	-rm -rf bochs/iso
	-mkdir -p bochs/iso/boot/grub
	cp bochs/grub.cfg bochs/iso/boot/grub/
	cp objects/kernel.stripped bochs/iso/kernel
	grub-mkrescue -o bochs/boot.iso bochs/iso

boot: bochs/boot.iso
	(cd bochs/; nice -20 bochs -q -f bochsrc)

boot-gdb: bochs/boot.iso
	(cd bochs/; nice -20 bochs-gdb -q -f bochsrc.gdb)

objects/kernel: objects/multiboot2.o objects/window.o src/link32.ld | objects
	x86_64-unknown-elf-ld  --no-warn-mismatch -z max-page-size=4096 -Tsrc/link32.ld -o objects/kernel objects/multiboot2.o objects/window.o

objects/kernel.stripped: objects/kernel | objects
	x86_64-unknown-elf-strip -o objects/kernel.stripped objects/kernel

objects/multiboot2.o: src/multiboot2.s | objects
	x86_64-unknown-elf-as --gstabs --32 -o objects/multiboot2.o src/multiboot2.s

objects/window.o: src/window.s | objects
	x86_64-unknown-elf-as --gstabs --32 -o objects/window.o src/window.s

clean:
	-rm -rf objects bochs/iso bochs/boot.iso

objects:
	-mkdir -p objects

compile: objects/kernel

debugger:
	gdb-bochs -x gdb-commands objects/kernel	

all: bochs/boot.iso
