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
    u8 event;
    char ascii = sc_to_ascii(scancode, &event);
    if (event != KEY_DOWN) return;

    print_char(ascii, 0x04);
}


