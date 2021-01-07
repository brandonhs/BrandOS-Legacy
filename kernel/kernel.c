#define STARTUP_MESSAGE "BrandOS kernel loaded.\n"

#include "../drivers/display.h"

void kmain() {
    print_string(STARTUP_MESSAGE, 0x04);
}