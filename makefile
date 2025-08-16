TARGET = kernel.elf
ISO = Valkyrie.iso

CC = gcc
LD = ld
ASM = nasm

CFLAGS = -m32 -ffreestanding -fno-pie -fno-stack-protector -Wall -Wextra -nostdlib -fno-builtin
LDFLAGS = -m elf_i386 -T linker.ld

SRCS = kernel.c kernel.asm
OBJS = kernel.o kernelasm.o

.PHONY: all run clean

all: $(ISO)

kernel.o: kernel.c
	$(CC) $(CFLAGS) -c $< -o $@

kernelasm.o: kernel.asm
	$(ASM) -f elf32 $< -o $@

$(TARGET): $(OBJS) linker.ld
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

$(ISO): $(TARGET) grub.cfg
	mkdir -p isodir/boot/grub
	cp $(TARGET) isodir/boot/
	cp grub.cfg isodir/boot/grub/
	grub-mkrescue -o $(ISO) isodir

run: $(ISO)
	qemu-system-i386 -cdrom $(ISO)

clean:
	rm -f $(OBJS) $(TARGET)
	rm -rf isodir
	rm -f $(ISO)