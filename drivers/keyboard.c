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

char sc_to_ascii(u8 scancode, u8 *event) {
    char ascii;
    *event = KEY_DOWN;
    switch (scancode) {
        case 0x0: // ERROR
            ascii = 0;
            break;
        case 0x1: // ESC
            ascii = '\e';
            break;
        case 0x2: // 1
            ascii = '1';
            break;
        case 0x3: // 2
            ascii = '2';
            break;
        case 0x4: // 3
            ascii = '3';
            break;
        case 0x5: // 4
            ascii = '4';
            break;
        case 0x6: // 5
            ascii = '5';
            break;
        case 0x7: // 6
            ascii = '6';
            break;
        case 0x8: // 7
            ascii = '7';
            break;
        case 0x9: // 8
            ascii = '8';
            break;
        case 0x0A: // 9
            ascii = '9';
            break;
        case 0x0B: // 0
            ascii = '0';
            break;
        case 0x0C: // -
            ascii = '-';
            break;
        case 0x0D: // +
            ascii = '+';
            break;
        case 0x0E: // backspace
            ascii = '\b';
            break;
        case 0x0F: // HT (TAB)
            ascii = '\t';
            break;
        case 0x10: // Q
            ascii = 'Q';
            break;
        case 0x11: // W
            ascii = 'W';
            break;
        case 0x12: // E
            ascii = 'E';
            break;
        case 0x13: // R
            ascii = 'R';
            break;
        case 0x14: // T
            ascii = 'T';
            break;
        case 0x15: // Y
            ascii = 'Y';
            break;
        case 0x16: // U
            ascii = 'U';
            break;
        case 0x17: // I
            ascii = 'I';
            break;
        case 0x18: // O
            ascii = 'O';
            break;
        case 0x19: // P
            ascii = 'P';
            break;
		case 0x1A: // [
            ascii = '[';
            break;
		case 0x1B: // ]
            ascii = ']';
            break;
		case 0x1C: // ENTER
			ascii = '\n';
			break;
		case 0x1D:
			kprint("LCtrl");
			break;
		case 0x1E: // A
            ascii = 'A';
            break;
		case 0x1F: // S
            ascii = 'S';
            break;
        case 0x20: // D
            ascii = 'D';
            break;
        case 0x21: // F
            ascii = 'F';
            break;
        case 0x22: // G
            ascii = 'G';
            break;
        case 0x23: // H
            ascii = 'H';
            break;
        case 0x24: // J
            ascii = 'J';
            break;
        case 0x25: // K
            ascii = 'K';
            break;
        case 0x26: // L
            ascii = 'L';
            break;
        case 0x27: // ;
            ascii = ';';
            break;
        case 0x28: // '
            ascii = '\'';
            break;
        case 0x29: // `
            ascii = '`';
            break;
		case 0x2A: // lShift
			kprint("LShift");
			break;
		case 0x2B: // '\'
            ascii = '\\';
            break;
		case 0x2C: // Z
            ascii = 'Z';
            break;
		case 0x2D: // X
            ascii = 'X';
            break;
		case 0x2E: // C
            ascii = 'C';
            break;
		case 0x2F: // V
            ascii = 'V';
            break;
        case 0x30: // B
            ascii = 'B';
            break;
        case 0x31: // N
            ascii = 'N';
            break;
        case 0x32: // M
            ascii = 'M';
            break;
        case 0x33: // ,
            ascii = ',';
            break;
        case 0x34: // .
            ascii = '.';
            break;
        case 0x35: // /
            ascii = '/';
            break;
        case 0x36: // rShift
            kprint("Rshift");
            break;
        case 0x37: // keypad *
            kprint("Keypad *");
            break;
        case 0x38: // lAlt
            kprint("LAlt");
            break;
        case 0x39: // ' '
            ascii = ' ';
            break;
        default:
            if (scancode <= 0x7f) {
                ascii = '?';
                *event = UNKNOWN_KEY_DOWN;
            } else if (scancode <= 0x39 + 0x80) {
                *event = KEY_UP;
                u8 *e;
                ascii = sc_to_ascii(scancode - 0x80, e);
            } else {
                *event = UNKNOWN_KEY_UP;
            }
            break;
    }
    return ascii;
}
