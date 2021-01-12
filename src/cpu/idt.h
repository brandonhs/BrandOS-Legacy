#ifndef IDT_H
#define IDT_H

#include "ktypes.h"

typedef struct {
    u16 offset_low;
    u16 selector;
    u8 zero;
    u8 flags;
    u16 offset_high;
} __attribute__((packed)) idt_gate_t;

typedef struct {
    u16 limit;
    u32 base;
} __attribute__((packed)) idt_regiseter_t;

idt_gate_t IDT[256];
idt_regiseter_t idt_reg;


void set_idt_gate(int n, u32 handler);
void set_idt();


#define low_16(address) (u16)((address) & 0xffff)
#define high_16(address) (u16)((address >> 16) & 0xffff)

#endif
