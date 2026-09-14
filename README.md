# Valkyrie Kernel

Valkyrie is a small 32-bit x86 kernel written in C and NASM assembly. It is
packaged as a bootable GRUB ISO and runs in QEMU. Once booted, it displays a
simple VGA text-mode command prompt with keyboard input.

## Requirements

Build and run the project on Linux with these tools available:

- `make`
- a GCC toolchain with 32-bit compilation support
- NASM
- GNU `ld`
- GRUB's `grub-mkrescue`
- `xorriso` (used by `grub-mkrescue` to create the ISO)
- `mtools` (provides `mformat`, used during ISO creation)
- QEMU for x86 (`qemu-system-i386`)

On Debian or Ubuntu, install them with:

```bash
sudo apt update
sudo apt install build-essential gcc-multilib nasm grub-pc-bin xorriso mtools qemu-system-x86
```

On Arch Linux, the equivalent packages are typically:

```bash
sudo pacman -S --needed base-devel gcc-multilib nasm grub xorriso mtools qemu-system-x86
```

## Build and run

Clone the repository and enter it:

```bash
git clone <repository-url>
cd Valkyrie-Kernel
```

Create the bootable ISO:

```bash
make
```

This produces `Valkyrie.iso`. Start it in QEMU with:

```bash
make run
```

QEMU opens a window and boots directly to the `valkyrie>` prompt. To stop the
emulator, close that window or press `Ctrl+C` in the terminal that ran `make run`.

To perform both steps in one command, run:

```bash
make run
```

`make run` builds the ISO first when it is missing or out of date.

## Using the kernel

The prompt currently accepts a US keyboard layout and supports these commands:

| Command | Description |
| --- | --- |
| `help` | List the available commands. |
| `clear` | Clear the display. |
| `about` | Show kernel information. |
| `echo <text>` | Print `<text>` back to the screen. |

For example:

```text
valkyrie> echo hello, Valkyrie!
hello, Valkyrie!
valkyrie> about
```

## Clean build artifacts

Remove the generated object files, ELF executable, ISO, and temporary ISO
directory:

```bash
make clean
```

Then rebuild with `make run`.

## Project layout

| File | Purpose |
| --- | --- |
| `kernel.c` | Kernel code: VGA output, keyboard handling, interrupts, and shell commands. |
| `kernel.asm` | Multiboot header and assembly entry point. |
| `linker.ld` | Places the kernel at the 1 MiB load address. |
| `grub.cfg` | GRUB menu entry that loads `kernel.elf`. |
| `makefile` | Builds the ELF, creates the ISO, and launches QEMU. |

## Troubleshooting

If `nasm: command not found`, install NASM. If `grub-mkrescue` or `xorriso` is
missing, install the GRUB and xorriso packages listed above. If ISO creation
reports that `mformat` failed or is missing, install `mtools`. If QEMU is not
found, install the `qemu-system-x86` package.

The build uses `gcc -m32`. On distributions where that flag fails due to missing
32-bit support, install the distribution's 32-bit GCC multilib package (for
example, `gcc-multilib` on Debian/Ubuntu or Arch).

## License

This project is released under the [MIT License](LICENSE).
