#ifndef idt_hpp_included
#define idt_hpp_included

#include <stdint.h>

void init_idt();

void isr(uint8_t id, void (*isr) (), uint8_t dpl);

void validate_idt();

#endif
