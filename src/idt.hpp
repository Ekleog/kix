#ifndef idt_hpp_included
#define idt_hpp_included

#include <stdint.h>

namespace idt
{
   struct idt_elem
   {
      uint16_t low_offset;
      uint16_t selector;
      uint16_t settings;
      uint16_t high_offset;
   };

   struct idtr
   {
      uint16_t limit;
      idt_elem *base;
   } __attribute__ ((packed));

   extern idtr IDTR;
   extern idt_elem IDT[256];

   inline void init()
   {
      IDTR.limit  = 256 * sizeof(idt_elem);
      IDTR.base   = IDT;
      asm volatile ("lidt %0" : : "m"(IDTR));
   }

   inline void isr(uint8_t id, void (*isr) (), uint8_t dpl)
   {
      uint16_t selector;
      asm volatile ("movw %0, %%cs" : "=g"(selector));

      uint32_t offset = reinterpret_cast<uint32_t>(isr);

      IDT[id].low_offset   = offset & 0xFFFF;
      IDT[id].selector     = selector;
      IDT[id].settings     = 0x8E00 | static_cast<uint16_t>(dpl << 13);
      IDT[id].high_offset  = static_cast<uint16_t>(offset >> 16);
   }

   inline void validate()
   {
      asm volatile ("sti");
   }
}

#endif
