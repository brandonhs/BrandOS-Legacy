#include "keyboard.h"
#include "ports.h"

#include "../cpu/isr.h"
#include "../cpu/ktypes.h"
#include "display.h"


const char kbd_us[128] = {
    0,
    '\e', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 
    0,
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
    0,
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 
    0, 
    '*', 
    0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '-', 0, 0, 0, '+', 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
};


key_callback_t key_func;

void keyboard_callback(registers_t r) {
    u8 scancode = inb(0x60);
    u8 event;
    char ascii = sc_to_ascii(scancode, &event);
    key_func(ascii, event);
}

void init_keyboard(key_callback_t f) {
    key_func = f;
    register_interrupt_handler(IRQ1, keyboard_callback);
}

char sc_to_ascii(u8 scancode, u8 *event) {
    char ascii;
    *event = KEY_DOWN;
    if (scancode & 0x80) {
        *event = KEY_UP;
        return 0;
    }
    ascii = kbd_us[scancode];
    return ascii;
}
