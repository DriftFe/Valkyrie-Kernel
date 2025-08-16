# Valkyrie-Kernel

A minimal x86 (demo) kernel written in C and Assembly, bootable with GRUB.

## Prerequisites

Before building and running Valkyrie, make sure you have the following tools installed:

### Ubuntu/Debian:
```bash
sudo apt update
sudo apt install build-essential nasm qemu-system-x86 grub-pc-bin xorriso
```

### Fedora/RHEL:
```bash
sudo dnf install gcc nasm qemu grub2-tools xorriso
```

### Arch Linux:
```bash
sudo pacman -S base-devel nasm qemu grub xorriso
```

### macOS (with Homebrew):
```bash
brew install nasm qemu grub xorriso
# You may also need: brew install i386-elf-gcc
```

## Installation

1. **Clone the repository:**
   ```bash
   git clone https://github.com/yourusername/valkyrie-kernel.git
   cd valkyrie-kernel
   ```

2. **Build and run in one command:**
   ```bash
   make && make run
   ```

This will compile the kernel and run it in QEMU.

## Troubleshooting

### "Command not found" errors:
Make sure all prerequisites are installed. On some systems, you might need:
```bash
# For 32-bit compilation support
sudo apt install gcc-multilib
```

### QEMU doesn't start:
Try using a different QEMU binary:
```bash
qemu-system-i386 -cdrom Valkyrie.iso
# or
qemu -cdrom Valkyrie.iso
```

### Permission issues:
Make sure the makefile is executable:
```bash
chmod +x makefile
```

### Build errors:
If you get linking errors, ensure you have the correct GCC flags:
```bash
gcc -m32 -ffreestanding -fno-pie -fno-stack-protector -Wall -Wextra -nostdlib -fno-builtin -c kernel.c -o kernel.o
```

## Current Features (idk I might work on it, but I'm not confident in myself)

- ✅ Multiboot compliance (GRUB bootable)
- ✅ VGA text mode output
- ✅ Basic kernel structure
- ❌ Keyboard input
- ❌ Memory management  
- ❌ File system
- ❌ Multitasking

ty for visitng :3

---

**Happy kernel hacking!** 🔥
