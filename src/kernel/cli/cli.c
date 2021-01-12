#include "cli.h"
#include "../../drivers/display.h"
#include "../../drivers/keyboard.h"

u8 initial_offset;

char buffer[256];
u8 offset;
u8 row;

void init_row();

void user_input(char a, u8 event) {
    if (event == KEY_DOWN) {
        if (a == '\n') {
            send_command();
        } else if (a == '\b') { // TODO implement backspace in string.c
            if (offset > initial_offset) {
                offset--;
                buffer[offset-initial_offset] = ' ';
                kprint_char_at(offset, row, 0x20, 0x07);
            }
        } else {
            print_char(a, 0x0f);
            buffer[(offset++)-initial_offset] = a;
        }
    }
}

void send_command() {
    print_nl();
    kprint("You typed: ");
    print_string(buffer, 0x03);
    for (int i = 0; buffer[i] != 0; i++) {
        buffer[i] = 0;
    }
    print_nl();
    print_nl();
    init_row();
}

void init_cli() {
    init_keyboard(user_input);
    init_row();
}

void init_row() {
    print_string("> ", 0x07);

    int x, y;
    get_cursor_pos(&x, &y);
    initial_offset = x;
    row = y;
    offset = initial_offset;
}
