#include "keyboard.h"
#include "ports.h"

#include "../cpu/isr.h"
#include "../cpu/ktypes.h"
#include "display.h"


key_callback_t key_func;

void keyboard_callback(registers_t r) {
    u8 scancode = inb(0x60);
    key_func(scancode);
}

void init_keyboard(key_callback_t f) {
    key_func = f;
    register_interrupt_handler(IRQ1, keyboard_callback);
}
