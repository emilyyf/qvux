CFLAGS  = -Iinclude -I. -std=c99 -Wall -m32
CFLAGS += -fno-stack-protector -ffreestanding -nostdlib -fno-builtin

SOURCES =                \
	src/loader.s           \
	src/main.c             \
	src/tty.c              \
	src/string.c

OBJECTS = $(patsubst src/%.s,build/%.o,$(patsubst src/%.c,build/%.o,$(SOURCES)))

build/%.o: src/%.c
	clang $(CFLAGS) -o $@ -c $<

build/%.o: src/%.s
	nasm -o $@ $< -f elf32

build/qvux.bin: src/linker.ld $(OBJECTS)
	ld.lld -T $< -o $@ $(OBJECTS)

clean:
	rm build/* &
	rm qvux.iso &

qvux.iso: build/qvux.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp $< iso/boot/
	cp grub.cfg iso/boot/grub/grub.cfg
	grub-mkrescue --output=$@ iso
	rm -rf iso

run: qvux.iso
	qemu-system-i386 $< &

all: qvux.iso
	echo "done"