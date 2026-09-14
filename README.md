# Valkyrie Kernel :3

Valkyrie is a tiny 32-bit x86 kernel written in C and NASM assembly.

It boots through GRUB, runs inside QEMU, and gives you a little VGA text-mode shell to play with. It's not Linux, it's not Windows, and it definitely isn't trying to be either.

It's just a silly little kernel doing its best. >w<

## ✨ What is this?

Valkyrie currently has:

- 🐧 GRUB booting
- 🧠 32-bit x86 kernel code
- 💻 VGA text-mode output
- ⌨️ Keyboard input
- ⚡ Interrupt handling
- 🐚 A tiny command shell
- 💿 Bootable ISO generation
- 🖥️ QEMU support
- 💕 A suspicious amount of enthusiasm for low-level programming

Once booted, Valkyrie drops you into:

```text
valkyrie>
```

and waits patiently for you to type something.

---

## 🛠️ Requirements

You'll need the following tools installed on Linux:

- `make`
- GCC with 32-bit compilation support
- NASM
- GNU `ld`
- GRUB's `grub-mkrescue`
- `xorriso`
- `mtools`
- QEMU for x86 (`qemu-system-i386`)

### Debian / Ubuntu

```bash
sudo apt update
sudo apt install build-essential gcc-multilib nasm grub-pc-bin xorriso mtools qemu-system-x86
```

### Arch Linux

```bash
sudo pacman -S --needed base-devel gcc-multilib nasm grub xorriso mtools qemu-system-x86
```

If your distro decides to put one of these somewhere weird, that's between you and your package manager. :3

---

## 📦 Build

Clone the repository:

```bash
git clone https://github.com/DriftFe/Valkyrie-Kernel.git
cd Valkyrie-Kernel
```

Then build the bootable ISO:

```bash
make
```

This produces:

```text
Valkyrie.iso
```

A tiny bootable ISO containing your tiny kernel. Yay! 🎀

---

## 🚀 Run

The easiest way to build and launch Valkyrie is:

```bash
make run
```

QEMU will open and boot directly into the Valkyrie shell:

```text
valkyrie>
```

Congratulations. Your computer is now running a kernel you made yourself.

That's pretty heckin' cool. 💖

To stop QEMU, close its window or press `Ctrl+C` in the terminal running `make run`.

---

## 🐚 The little shell

The shell currently uses a **US keyboard layout** and understands these commands:

| Command | Description |
| --- | --- |
| `help` | Show the available commands. |
| `clear` | Clear the screen. |
| `about` | Show information about the kernel. |
| `echo <text>` | Print `<text>` back to the screen. |

For example:

```text
valkyrie> echo hello, Valkyrie!
hello, Valkyrie!

valkyrie> about
```

Very advanced stuff.

Absolutely cutting-edge technology. 😌

---

## 🧹 Clean

Made a mess? No worries.

Remove the generated object files, ELF executable, ISO, and temporary ISO directory:

```bash
make clean
```

Then rebuild:

```bash
make run
```

and you're back in business. ✨

---

## 📁 Project structure

| File | Purpose |
| --- | --- |
| `kernel.c` | Kernel code: VGA output, keyboard handling, interrupts, and shell commands. |
| `kernel.asm` | Multiboot header and assembly entry point. |
| `linker.ld` | Places the kernel at the 1 MiB load address. |
| `grub.cfg` | GRUB configuration that loads `kernel.elf`. |
| `makefile` | Builds the kernel, creates the ISO, and launches QEMU. |

The project is intentionally small so that the underlying kernel code stays easy to explore and understand.

---

## 🩷 Troubleshooting

### `nasm: command not found`

NASM isn't installed.

Install it using your distribution's package manager.

### `grub-mkrescue: command not found`

Install the GRUB tooling listed in the requirements section.

### `xorriso: command not found`

Install `xorriso`.

GRUB uses it while creating the bootable ISO.

### `mformat: command not found`

Install `mtools`.

`mformat` is provided by the `mtools` package.

You can verify that it is installed with:

```bash
mformat -V
```

### ISO creation fails around `mformat`

Make sure `mtools` is installed correctly:

```bash
mformat -V
```

If the command isn't found, install `mtools` and try again.

### `qemu-system-i386: command not found`

Install the QEMU x86 package.

On Arch Linux:

```bash
sudo pacman -S qemu-system-x86
```

### `gcc -m32` doesn't work

Your GCC installation probably doesn't have 32-bit compilation support enabled.

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

## 🗺️ What's next?

Valkyrie is still very much a work in progress.

Some things I'd like to add eventually:

- 💾 A filesystem
- 📂 File and directory commands
- 🧠 Memory management
- ⏱️ A timer
- 🖥️ Better terminal support
- 💿 Disk I/O
- 🌐 Networking
- 🧩 A virtual filesystem layer
- 🛠️ More kernel subsystems
- 🎀 An unnecessarily cute shell

The filesystem is next.

Because apparently making a computer from scratch wasn't enough. :3

---

## 📜 License

Valkyrie is released under the [MIT License](LICENSE).

Do whatever you want with it.

Make it better. Make it worse. Add networking. Make the shell pink.

Just have fun with it. 🎀
