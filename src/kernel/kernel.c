#define STARTUP_MESSAGE "BrandOS kernel loaded.\n\n"

#include "../drivers/display.h"
#include "../drivers/ports.h"

#include "../cpu/isr.h"

#include "../drivers/keyboard.h"
#include "cli/cli.h"


void kmain() {
    kprint(STARTUP_MESSAGE);

    isr_install();
    asm volatile("sti");

    init_cli();
}

