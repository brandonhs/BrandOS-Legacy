#define STARTUP_MESSAGE "BrandOS kernel loaded.\n"

#include "../drivers/display.h"
#include "../drivers/ports.h"

void kmain() {
    print_string(STARTUP_MESSAGE, 0x04);

    char c = 0;

    while (1) {
        if (inb(0x60) != c) {
            c = inb(0x60);
            if (c > 0) {
                print_char(c, 0x0f);
            }
        }
    }
}