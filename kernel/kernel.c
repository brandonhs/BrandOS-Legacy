#define STARTUP_MESSAGE "BrandOS kernel loaded.\n"

#include "../drivers/display.h"
#include "../drivers/ports.h"


void kmain() {
    kprint(STARTUP_MESSAGE);
}