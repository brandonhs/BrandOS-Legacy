#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "../cpu/ktypes.h"

#define KEY_UP 0
#define KEY_DOWN 1
#define UNKNOWN_KEY_DOWN 2
#define UNKNOWN_KEY_UP 3


typedef void (*key_callback_t)(u8 scancode);

void init_keyboard(key_callback_t f); // initialize keyboard driver
char sc_to_ascii(u8 scancode, u8 *event);

#endif
