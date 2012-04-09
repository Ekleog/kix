#ifndef util_hpp_included
#define util_hpp_included 1

#include "types.hpp"

extern "C" inline byte inb(u16 port)
{
   byte ret;
   __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
   return ret;
}
extern "C" inline void outb(u16 port, u8 byte)
{
   __asm__ volatile ("outb %0, %1" : : "a"(byte), "Nd"(port));
}

extern "C" inline void io_wait()
{
   // TODO: Find a really unused port
   __asm__ volatile ("outb %%al, $0x80" : : "a"(0));
}

#endif
