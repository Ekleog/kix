#ifndef idt_hpp_included
#define idt_hpp_included

#include "types.hpp"

void init_idt();

void isr(u8 id, void (*isr) (), byte dpl);

void validate_idt();

#endif
