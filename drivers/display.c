#include "display.h"
#include "ports.h"

// private display functions
int get_cursor_offset();
void set_cursor_offset(int offset);

// private util functions
int get_offset(int col, int row);
int get_offset_row(int offset);
int get_offset_col(int offset);
int move_offset_row(int offset, int row_off);
//void vga_mem_copy(int source_row, int dest_row);

void kprint(char* message) {
    print_string(message, WHITE_ON_BLACK);
}

char *itoa(int val, int base) {
    static char buf[32] = {0};
    int i = 30;
    for (; val && i; --i, val /= base) {
        buf[i] = "0123456789abcdef"[val % base];
    }
    return &buf[i + 1];
}

void print_char(char character, char attributes) {
    int offset = get_cursor_offset();
    if (character == '\n') {
        offset = move_offset_row(offset, 1);
    } else if (character == '\b') {
        if (offset <= 0) offset = MAX_COLS-1;
        else offset--;
        set_cursor_offset(offset);
        write_character_to_memory(offset, 0x20, 0x07); // default no character
    } else {
        write_character_to_memory(offset, character, attributes);
        offset += 1;
    }
    if (get_offset_row(offset) > MAX_ROWS-1) {
        offset = move_offset_row(offset, -1);
        scroll_ln(1);
    }
    set_cursor_offset(offset);
}

void print_string(char* message, char attributes) {
    for (int i = 0; message[i] != 0; i++) {
        print_char(message[i], attributes);
    }
}

void print_nl() {
    print_char('\n', 0x00);
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

int move_offset_row(int offset, int row_off) {
    int row = get_offset_row(offset);
    offset = get_offset(0, row+row_off); // move col = 0, row += 1
    return offset;
}

void vga_mem_copy(int source_row, int dest_row) {
    if (source_row == dest_row) return; // dont waste time if source == dest

    unsigned short num_bytes = MAX_COLS*2;

    char *source_mem = (char*)(VGA_TEXT_MEMORY + get_offset(0, source_row)*2);
    char *dest_mem = (char*)(VGA_TEXT_MEMORY + get_offset(0, dest_row)*2);

    for (int i = 0; i < num_bytes; i++) {
        *(dest_mem+i) = *(source_mem+i);
    }
}

void scroll_ln(int offset) {
    // TODO: add variable offset and scroll buffer
    for (int i = 1; i <= MAX_ROWS; i++) {
        vga_mem_copy(i, i-1);
    }
}
