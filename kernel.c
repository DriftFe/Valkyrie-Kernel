#include <stdint.h>
#include <stddef.h>

// VGA text mode buffer thingi idk
#define VGA_ADDRESS 0xB8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

// COLORSSSSSSS
#define VGA_COLOR_BLACK 0
#define VGA_COLOR_BLUE 1
#define VGA_COLOR_GREEN 2
#define VGA_COLOR_CYAN 3
#define VGA_COLOR_RED 4
#define VGA_COLOR_MAGENTA 5
#define VGA_COLOR_BROWN 6
#define VGA_COLOR_LIGHT_GREY 7
#define VGA_COLOR_DARK_GREY 8
#define VGA_COLOR_LIGHT_BLUE 9
#define VGA_COLOR_LIGHT_GREEN 10
#define VGA_COLOR_LIGHT_CYAN 11
#define VGA_COLOR_LIGHT_RED 12
#define VGA_COLOR_LIGHT_MAGENTA 13
#define VGA_COLOR_YELLOW 14
#define VGA_COLOR_WHITE 15

// Keyboard :3
#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

// IDT or smth
#define IDT_SIZE 256
#define INTERRUPT_GATE 0x8E
#define KERNEL_CODE_SEGMENT_OFFSET 0x08

#define ENTER_KEY_CODE 0x1C
#define BACKSPACE_KEY_CODE 0x0E

// Global vars
static uint16_t* vga_buffer = (uint16_t*)VGA_ADDRESS;
static uint32_t vga_index = 0;
static uint8_t current_color = VGA_COLOR_LIGHT_GREY;

static char keyboard_buffer[256];
static uint8_t keyboard_buffer_index = 0;

// IDT entry uhh structure 
struct IDT_entry {
    uint16_t offset_lowerbits;
    uint16_t selector;
    uint8_t zero;
    uint8_t type_attr;
    uint16_t offset_higherbits;
} __attribute__((packed));

struct IDT_entry IDT[IDT_SIZE];

// IDT pointer structure
struct IDT_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

struct IDT_ptr idt_ptr;

// Port I/O stuff
static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ __volatile__("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

static inline void outb(uint16_t port, uint8_t val) {
    __asm__ __volatile__("outb %0, %1" : : "a"(val), "Nd"(port));
}

// String functions
size_t strlen(const char* str) {
    size_t len = 0;
    while (str[len]) len++;
    return len;
}

int strcmp(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

// VGA functions
void vga_clear_screen() {
    for (uint32_t i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        vga_buffer[i] = ((uint16_t)current_color << 8) | ' ';
    }
    vga_index = 0;
}

void vga_set_color(uint8_t foreground, uint8_t background) {
    current_color = (background << 4) | (foreground & 0x0F);
}

void vga_newline() {
    vga_index = (vga_index / VGA_WIDTH + 1) * VGA_WIDTH;
    if (vga_index >= VGA_WIDTH * VGA_HEIGHT) {
        // Scroll screen func
        for (uint32_t i = 0; i < VGA_WIDTH * (VGA_HEIGHT - 1); i++) {
            vga_buffer[i] = vga_buffer[i + VGA_WIDTH];
        }
        for (uint32_t i = VGA_WIDTH * (VGA_HEIGHT - 1); i < VGA_WIDTH * VGA_HEIGHT; i++) {
            vga_buffer[i] = ((uint16_t)current_color << 8) | ' ';
        }
        vga_index = VGA_WIDTH * (VGA_HEIGHT - 1);
    }
}

void vga_putchar(char c) {
    if (c == '\n') {
        vga_newline();
        return;
    }
    
    if (vga_index >= VGA_WIDTH * VGA_HEIGHT) {
        vga_newline();
    }
    
    vga_buffer[vga_index] = ((uint16_t)current_color << 8) | c;
    vga_index++;
}

void vga_print(const char* str) {
    for (size_t i = 0; str[i] != '\0'; i++) {
        vga_putchar(str[i]);
    }
}

void vga_backspace() {
    if (vga_index > 0) {
        vga_index--;
        vga_buffer[vga_index] = ((uint16_t)current_color << 8) | ' ';
    }
}

// Keyboard scancode to ASCII mapping (US layout.. cuz why not)
static char scancode_to_ascii[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
    0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
    '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    '-', 0, 0, 0, '+', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

// Command functions
void cmd_help() {
    vga_print("Available commands:\n");
    vga_print("  help    - Show this help message\n");
    vga_print("  clear   - Clear the screen\n");
    vga_print("  about   - About Valkyrie Kernel\n");
    vga_print("  echo    - Echo text back\n");
}

void cmd_clear() {
    vga_clear_screen();
}

void cmd_about() {
    vga_set_color(VGA_COLOR_LIGHT_CYAN, VGA_COLOR_BLACK);
    vga_print("Valkyrie Kernel v0.1.0\n");
    vga_set_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    vga_print("A minimal x86 kernel with keyboard support\n");
    vga_print("Written in C and x86 Assembly\n");
}

void cmd_echo(const char* args) {
    vga_print(args);
    vga_print("\n");
}

// Process command
void process_command(const char* cmd) {
    if (cmd[0] == '\0') {
        return;
    }
    
    if (strcmp(cmd, "help") == 0) {
        cmd_help();
    } else if (strcmp(cmd, "clear") == 0) {
        cmd_clear();
    } else if (strcmp(cmd, "about") == 0) {
        cmd_about();
    } else if (cmd[0] == 'e' && cmd[1] == 'c' && cmd[2] == 'h' && cmd[3] == 'o' && cmd[4] == ' ') {
        cmd_echo(cmd + 5);
    } else {
        vga_set_color(VGA_COLOR_LIGHT_RED, VGA_COLOR_BLACK);
        vga_print("Unknown command: ");
        vga_print(cmd);
        vga_print("\n");
        vga_set_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
        vga_print("Type 'help' for available commands\n");
    }
}

void print_prompt() {
    vga_set_color(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
    vga_print("valkyrie> ");
    vga_set_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
}

// Keyboard interrupt handler
void keyboard_handler_main(uint8_t scancode) {
    
    if (scancode < 128) {
        if (scancode == ENTER_KEY_CODE) {
            vga_putchar('\n');
            keyboard_buffer[keyboard_buffer_index] = '\0';
            process_command(keyboard_buffer);
            keyboard_buffer_index = 0;
            print_prompt();
        } else if (scancode == BACKSPACE_KEY_CODE) {
            if (keyboard_buffer_index > 0) {
                keyboard_buffer_index--;
                vga_backspace();
            }
        } else {
            char c = scancode_to_ascii[scancode];
            if (c != 0 && keyboard_buffer_index < 255) {
                keyboard_buffer[keyboard_buffer_index++] = c;
                vga_putchar(c);
            }
        }
    }
    
    }

// Assembly wrapper for keyboard handler (ASSEMBLY >~<)
__asm__(
    ".global keyboard_handler\n"
    ".type keyboard_handler, @function\n"
    "keyboard_handler:\n"
    "    pusha\n"
    "    inb $0x60, %al\n"
    "    movzbl %al, %eax\n"
    "    push %eax\n"
    "    mov $0x20, %al\n"
    "    outb %al, $0x20\n"
    "    call keyboard_handler_main\n"
    "    add $4, %esp\n"
    "    popa\n"
    "    iret\n"
);

extern void keyboard_handler(void);

// IDT functions
static inline uint16_t get_cs() {
    uint16_t cs;
    __asm__ __volatile__("mov %%cs, %0" : "=r"(cs));
    return cs;
}

void idt_set_gate(uint8_t num, uint16_t selector, uint32_t handler) {
    IDT[num].offset_lowerbits = handler & 0xFFFF;
    IDT[num].selector = selector;
    IDT[num].zero = 0;
    IDT[num].type_attr = INTERRUPT_GATE;
    IDT[num].offset_higherbits = (handler >> 16) & 0xFFFF;
}

void idt_init() {
    // Clear IDT
    for (int i = 0; i < IDT_SIZE; i++) {
        IDT[i].offset_lowerbits = 0;
        IDT[i].selector = 0;
        IDT[i].zero = 0;
        IDT[i].type_attr = 0;
        IDT[i].offset_higherbits = 0;
    }
    
    idt_ptr.limit = (sizeof(struct IDT_entry) * IDT_SIZE) - 1;
    idt_ptr.base = (uint32_t)&IDT;
    
    // Set keyboard interrupt (IRQ1 = interrupt 0x21)
    uint16_t cs = get_cs();
    idt_set_gate(0x21, cs, (uint32_t)keyboard_handler);
    
    // Load IDT
    __asm__ __volatile__("lidt %0" : : "m"(idt_ptr));
}

// PIC (Programmable Interrupt Controller) initialization
void pic_init() {
    // ICW1 - begin initialization, autobots rollout thing
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    
    // ICW2 - remap offset address of IDT
    outb(0x21, 0x20); // Master PIC vector offset
    outb(0xA1, 0x28); // Slave PIC vector offset
    
    // ICW3 - setup cascading
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    
    // ICW4 - environment info
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    
    // Mask all interrupts except keyboard (IRQ1) :p
    outb(0x21, 0xFD);
    outb(0xA1, 0xFF);
}

void kernel_main() {
    // Clear screen with black background cuz OBV
    vga_set_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    vga_clear_screen();
    
    // Print welcome message
    vga_set_color(VGA_COLOR_LIGHT_CYAN, VGA_COLOR_BLACK);
    vga_print("=================================\n");
    vga_print("   Valkyrie Kernel v0.1.0\n");
    vga_print("=================================\n\n");
    vga_set_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    
    vga_print("Welcome to Valkyrie Kernel!\n");
    vga_print("Type 'help' for available commands.\n\n");
    
    // Initialize IDT and PIC
    idt_init();
    pic_init();
    
    // Enable interrupts heh..
    __asm__ __volatile__("sti");
    
    // Print first prompt
    print_prompt();
    
    // Infinite loop thing
    while (1) {
        __asm__ __volatile__("hlt");
    }
}
