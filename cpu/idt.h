#ifndef IDT_H
#define IDT_H

#include "ktypes.h"

typedef struct {
    u16 offset_low;
} __attribute((packed)) idt_gate_t;

#endif
