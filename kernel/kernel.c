#define STARTUP_MESSAGE "BrandOS kernel loaded.\n\n"

#include "../drivers/display.h"
#include "../drivers/ports.h"

#include "../cpu/isr.h"

#include "../drivers/keyboard.h"


void key_callback(u8 scancode);

void kmain() {
    kprint(STARTUP_MESSAGE);

    isr_install();

    asm volatile("sti");

    init_keyboard(key_callback);
}


void key_callback(u8 scancode) {
    char sc2ascii[] = {SCANCODE2ASCII_TABLE};
    char ascii = sc2ascii[scancode];
    if (ascii == 0) return;

    print_char(ascii, 0x04);
}


