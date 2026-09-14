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
=======
# Valkyrie Kernel :3

Valkyrie is a tiny 32-bit x86 kernel written in C and NASM assembly.

It boots through GRUB, runs inside QEMU, and gives you a cute little VGA text-mode shell to play with. It's not Linux, it's not Windows, and it definitely isn't trying to be either.

It's just a silly little kernel doing its best. >w<

## ✨ What is this?

Valkyrie currently has:

* 🐧 GRUB booting
* 🧠 32-bit x86 kernel code
* 💻 VGA text-mode output
* ⌨️ Keyboard input
* ⚡ Interrupt handling
* 🐚 A tiny command shell
* 💿 Bootable ISO generation
* 🖥️ QEMU support
* 💕 A suspicious amount of enthusiasm for low-level programming

Once booted, it drops you into:

```text
valkyrie>
```

and waits patiently for you to type something.

---

## 🛠️ Requirements

You'll need these installed on Linux:

* `make`
* GCC with 32-bit compilation support
* NASM
* GNU `ld`
* GRUB's `grub-mkrescue`
* `xorriso`
* `mtools` — provides `mformat`, which is used while creating the ISO
* QEMU for x86 (`qemu-system-i386`)

### Debian / Ubuntu
```bash
sudo apt update
sudo apt install build-essential gcc-multilib nasm grub-pc-bin xorriso mtools qemu-system-x86
```


On Arch Linux, the equivalent packages are typically:
=======
### Arch Linux
```bash
sudo pacman -S --needed base-devel gcc-multilib nasm grub xorriso mtools qemu-system-x86
```

<<<<<<< HEAD
## Build and run

Clone the repository and enter it:

```bash
git clone <https://github.com/DriftFe/Valkyrie-Kernel>
cd Valkyrie-Kernel
```

Create the bootable ISO:
=======
If your distro decides to put one of these somewhere weird, that's between you and your package manager. :3

---

## 💿 Build it

Clone the repository and hop into it:

```bash
git clone https://github.com/DriftFe/Valkyrie-Kernel
cd Valkyrie-Kernel
```

Then build the ISO:
```bash
make
```


This produces `Valkyrie.iso`. Start it in QEMU with:
=======
This produces:

```text
Valkyrie.iso
```

A tiny bootable ISO containing your tiny kernel. Yay! 🎀

---

## 🚀 Run it

You can build and launch Valkyrie with:

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
=======
`make run` builds the ISO first if it is missing or out of date, then launches QEMU.

You should eventually see:

```text
valkyrie>
```

Congratulations. Your computer is now running a kernel you made yourself.

That's pretty heckin' cool. 💖

To stop QEMU, close its window or press `Ctrl+C` in the terminal running `make run`.

---

## 🐚 The little shell

The prompt currently uses a **US keyboard layout** and understands these commands:

| Command       | What it does                        |
| ------------- | ----------------------------------- |
| `help`        | Shows the available commands.       |
| `clear`       | Clears the screen.                  |
| `about`       | Shows information about the kernel. |
| `echo <text>` | Prints your text back at you.       |
>>>>>>> 82efb2dee658990fdf4d5211a05f353b3f483cbb

For example:

```text
valkyrie> echo hello, Valkyrie!
hello, Valkyrie!
<<<<<<< HEAD
valkyrie> about
```

## Clean build artifacts

Remove the generated object files, ELF executable, ISO, and temporary ISO
directory:
=======

valkyrie> about
```

Very advanced stuff.

Absolutely cutting-edge technology. 😌

---

## 🧹 Clean everything

Made a mess? No worries.
>>>>>>> 82efb2dee658990fdf4d5211a05f353b3f483cbb

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
=======
This removes the generated object files, ELF executable, ISO, and temporary ISO directory.

Then:

```bash
make run
```

and you're back in business. ✨

---

## 📁 Project structure

| File         | Purpose                                                                     |
| ------------ | --------------------------------------------------------------------------- |
| `kernel.c`   | Kernel code: VGA output, keyboard handling, interrupts, and shell commands. |
| `kernel.asm` | Multiboot header and assembly entry point.                                  |
| `linker.ld`  | Places the kernel at the 1 MiB load address.                                |
| `grub.cfg`   | GRUB configuration that loads `kernel.elf`.                                 |
| `makefile`   | Builds the kernel, creates the ISO, and launches QEMU.                      |

It's small. It's cute. It boots.

What more could you want? :3

---

## 🩷 Troubleshooting

### `nasm: command not found`

NASM isn't installed.

Install it with your distro's package manager.

### `grub-mkrescue: command not found`

Install the GRUB tooling listed above.

### `xorriso: command not found`

Install `xorriso`.

GRUB uses it while creating the bootable ISO.

### `mformat: command not found`

Install `mtools`.

`mformat` is part of the `mtools` package and is used during ISO creation.

### ISO creation fails around `mformat`

Make sure `mtools` is installed correctly:

```bash
mformat -V
```

If that command isn't found, install `mtools` and try again.

### `qemu-system-i386: command not found`

Install the QEMU x86 package.

### `gcc -m32` doesn't work

Your GCC installation probably doesn't have 32-bit support enabled.

On Debian / Ubuntu:

```bash
sudo apt install gcc-multilib
```

On Arch:

```bash
sudo pacman -S gcc-multilib
```

Then try:

```bash
make
```

again.

---

## 💕 Why Valkyrie?

Because writing a kernel is fun.

Because `mov eax, 0` makes the brain go brrrr.

Because eventually you look at a black QEMU window displaying your own:

```text
valkyrie>
```

and realize:

**oh my god I made a computer thingy**

And that's pretty neat. :3

---

## 📜 License

Valkyrie is released under the [MIT License](LICENSE).

Do whatever you want with it.

Make it better. Make it worse. Add a filesystem. Add networking. Make the shell pink. Put it on real hardware.

Just have fun with it. 🎀
