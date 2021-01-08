#ifndef DISPLAY_H
#define DISPLAY_H

#define VGA_TEXT_MEMORY 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80

#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

#define WHITE_ON_BLACK 0x0f

char *itoa(int val, int base);

void write_character_to_memory(unsigned int offset, char character, char attributes);

void print_char(char character, char attributes);
void print_string(char* message, char attributes);
void print_nl();

void vga_mem_copy(int source_row, int dest_row);
void scroll_ln(int offset);

#endif