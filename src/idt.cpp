#include "idt.hpp"

#include "types.hpp"

struct idt_elem
{
   u16 low_offset;
   u16 selector;
   u16 settings;
   u16 high_offset;
};

struct idtr
{
   u16 limit;
   idt_elem *base;
} __attribute__ ((packed));

static idtr IDTR;
static idt_elem IDT[256];

void init_idt()
{
   IDTR.limit  = 256 * sizeof(idt_elem);
   IDTR.base   = IDT;
   __asm__ volatile ("lidt %0" : : "m"(IDTR));
}

void isr(u8 id, void (*isr) (), byte dpl)
{
   u16 selector;
   __asm__ volatile ("movw %0, %%cs" : "=g"(selector));

   u32 offset = reinterpret_cast<u32>(isr);

   IDT[id].low_offset   = offset & 0xFFFF;
   IDT[id].selector     = selector;
   IDT[id].settings     = 0x8E00 | static_cast<u16>(dpl << 13);
   IDT[id].high_offset  = static_cast<u16>(offset >> 16);
}

void validate_idt()
{
   __asm__ volatile ("sti");
}
