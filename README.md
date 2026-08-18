# Valkyrie Kernel :3

Valkyrie is a tiny little 32-bit x86 kernel written in C and NASM assembly.

It boots through GRUB, runs happily inside QEMU, and gives you a cute little VGA text-mode shell to play with. It's not trying to be Linux. It's not trying to be Windows. It's just a silly little kernel doing its best. >w<

## ✨ What is this?

Valkyrie is a small hobby kernel project that currently has:

* 🐧 GRUB booting
* 🧠 32-bit x86 kernel code
* 💻 VGA text-mode output
* ⌨️ Keyboard input
* ⚡ Interrupt handling
* 🐚 A tiny command shell
* 🖥️ QEMU support
* 💕 An unreasonable amount of affection for low-level programming
:p

It boots straight into:

```text
valkyrie>
```

and waits patiently for you to type something.

---

## 🛠️ Requirements

You'll need these tools installed:

* `make`
* GCC with 32-bit compilation support
* NASM
* GNU `ld`
* `grub-mkrescue`
* `xorriso`
* QEMU for x86 (`qemu-system-i386`)

### Debian / Ubuntu

```bash
sudo apt update
sudo apt install build-essential gcc-multilib nasm grub-pc-bin xorriso qemu-system-x86
```

### Arch Linux

```bash
sudo pacman -S --needed base-devel gcc-multilib nasm grub xorriso qemu-system-x86
```

If something explodes because your distro decided to put a package somewhere silly, check your package manager first. :3

---

## 💿 Build it

Clone the repository and hop into it:

```bash
git clone <repository-url>
cd Valkyrie-Kernel
```

Then:

```bash
make
```

If everything goes according to plan, you'll get:

```text
Valkyrie.iso
```

A tiny bootable ISO containing your tiny kernel. Yay! 🎀

---

## 🚀 Run it

The easiest way is:

```bash
make run
```

This builds the ISO if necessary and then launches QEMU.

You should eventually be greeted by:

```text
valkyrie>
```

Congratulations. Your computer is now running a kernel you made yourself. That's pretty heckin' cool. 💖

To stop QEMU, close its window or press `Ctrl+C` in the terminal running `make run`.

---

## 🐚 The little shell

Valkyrie currently understands a few commands:

| Command       | What it does                  |
| ------------- | ----------------------------- |
| `help`        | Shows the available commands. |
| `clear`       | Clears the screen.            |
| `about`       | Tells you about the kernel.   |
| `echo <text>` | Prints your text back at you. |

For example:

```text
valkyrie> echo hello, Valkyrie!
hello, Valkyrie!

valkyrie> about
```

Very advanced stuff. Absolutely cutting-edge technology. 😌

The keyboard currently uses a **US keyboard layout**.

---

## 🧹 Clean everything

Made a mess? No worries.

```bash
make clean
```

This removes:

* object files
* the kernel ELF
* `Valkyrie.iso`
* temporary ISO files

Then just:

```bash
make run
```

and you're back in business. ✨

---

## 📁 Project structure

| File         | Purpose                                                                |
| ------------ | ---------------------------------------------------------------------- |
| `kernel.c`   | The main kernel code — VGA, keyboard, interrupts, shell commands, etc. |
| `kernel.asm` | Multiboot header + assembly entry point.                               |
| `linker.ld`  | Tells the linker where to put the kernel (1 MiB).                      |
| `grub.cfg`   | GRUB configuration that loads `kernel.elf`.                            |
| `makefile`   | Handles building, ISO creation, and QEMU.                              |

It's small. It's cute. It boots. What more could you want? :3

---

## 🩷 Troubleshooting

### `nasm: command not found`

You don't have NASM installed.

Install it with your distro's package manager.

### `grub-mkrescue: command not found`

Install the GRUB tooling listed above.

### `xorriso: command not found`

Install `xorriso`.

GRUB uses it while creating the ISO.

### `qemu-system-i386: command not found`

Install the QEMU x86 package.

### `gcc -m32` doesn't work

Your GCC installation probably doesn't have 32-bit support enabled.

On Arch:

```bash
sudo pacman -S gcc-multilib
```

On Debian/Ubuntu:

```bash
sudo apt install gcc-multilib
```

Then try the build again.

---

## 💕 Why Valkyrie?

Because writing a kernel is fun.

Because `mov eax, 0` makes the brain go brrrr.

Because eventually you look at a black QEMU window displaying your own `valkyrie>` prompt and realize:

**oh my god I made a computer thingy**

And that's pretty neat. :3

---

## 📜 License

Valkyrie is released under the [MIT License](LICENSE).

Do whatever you want with it.

Make it better. Make it worse. Add a filesystem. Add networking. Make the shell pink. Put it on real hardware.

Just have fun with it. 🎀
