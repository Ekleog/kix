#ifndef pic_hpp_included
#define pic_hpp_included 1

#include <stdint.h>
#include "asm.hpp"

namespace pic
{
   constexpr uint16_t PIC1_CMD = 0x20,
                      PIC1_DTA = 0x21,

                      PIC2_CMD = 0xA0,
                      PIC2_DTA = 0xA1;

   inline void remap(uint8_t off1 = 0x50, uint8_t off2 = 0x58)
   {
      // Start initialization
      outb(PIC1_CMD, 0x11); io_wait();
      outb(PIC2_CMD, 0x11); io_wait();
      // Set offsets
      outb(PIC1_DTA, off1); io_wait();
      outb(PIC2_DTA, off2); io_wait();
      // Say who is the master/slave PIC
      outb(PIC1_DTA, 0x04); io_wait();
      outb(PIC2_DTA, 0x02); io_wait();
      // Set the 8086/88 mode
      outb(PIC1_DTA, 0x01); io_wait();
      outb(PIC2_DTA, 0x01); io_wait();
      // Set masks
      outb(PIC1_DTA, 0x00);
      outb(PIC2_DTA, 0x00);
   }
}

#endif
