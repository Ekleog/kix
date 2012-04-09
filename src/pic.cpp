#include "pic.hpp"

#include "types.hpp"
#include "util.hpp"

#define PIC1_CMD 0x20
#define PIC1_DTA 0x21

#define PIC2_CMD 0xA0
#define PIC2_DTA 0xA1

namespace pic
{
   void remap(u8 off1, u8 off2)
   {
      // Save masks
      u8 m1 = inb(PIC1_DTA);
      u8 m2 = inb(PIC2_DTA);
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
      // Restore masks
      outb(PIC1_DTA, m1);
      outb(PIC2_DTA, m2);
   }
}
