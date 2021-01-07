#define STARTUP_MESSAGE "BrandOS kernel loaded.\n"

#include "../drivers/display.h"

void kmain() {
    print_string(STARTUP_MESSAGE, 0x04);

    for (int i = 1; i < 30; i++) {
        char* str = itoa(i, 10);
        print_string(str, 0x0f);
        print_nl();
    }
}