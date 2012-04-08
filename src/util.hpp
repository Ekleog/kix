#ifndef util_hpp_included
#define util_hpp_included 1

#include "types.hpp"

extern "C" inline void outb(u16 port, u8 byte)
{
  __asm__ volatile ("outb %0, %1" : : "a"(byte), "Nd"(port));
}

#endif
