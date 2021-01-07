#include "display.h"
#include "ports.h"

// private display functions
int get_cursor_offset();
void set_cursor_offset(int offset);
void write_character_to_memory(unsigned int offset, char character, char attributes);

// private util functions
int get_offset(int col, int row);
int get_offset_row(int offset);
int get_offset_col(int offset);
int move_offset_to_newline(int offset);


void print_char(char character, char attributes) {
    int offset = get_cursor_offset();
    if (character == '\n') {
        offset = move_offset_to_newline(offset);
    } else {
        write_character_to_memory(offset, character, attributes);
        offset += 1;
    }
    set_cursor_offset(offset);
}

void print_string(char* message, char attributes) {
    for (int i = 0; message[i] != 0; i++) {
        print_char(message[i], attributes);
    }
}


int get_cursor_offset() {
    int offset = 0;
    outb(REG_SCREEN_CTRL, 14); // request high byte for cursor offset
    offset = inb(REG_SCREEN_DATA) << 8;
    outb(REG_SCREEN_CTRL, 15); // request low byte for cursor offset
    offset += inb(REG_SCREEN_DATA);
    return offset;
}

void set_cursor_offset(int offset) {
    outb(REG_SCREEN_CTRL, 14);
    outb(REG_SCREEN_DATA, (unsigned char)(offset >> 8)); // write to high byte
    outb(REG_SCREEN_CTRL, 15);
    outb(REG_SCREEN_DATA, (unsigned char)(offset & 0xff)); // write to low byte
}

void write_character_to_memory(unsigned int offset, char character, char attributes) {
    unsigned char *vidmem = (unsigned char*) VGA_TEXT_MEMORY;
    vidmem[offset*2] = character;
    vidmem[offset*2+1] = attributes;
}


int get_offset(int col, int row) {
    return row * MAX_COLS + col;
}

int get_offset_row(int offset) {
    return offset / MAX_COLS;
}

int get_offset_col(int offset) {
    return offset - get_offset_row(offset)*MAX_COLS;
}

int move_offset_to_newline(int offset) {
    int row = get_offset_row(offset);
    offset = get_offset(0, row+1); // move col = 0, row += 1
    return offset;
}
