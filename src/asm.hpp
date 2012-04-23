#ifndef util_hpp_included
#define util_hpp_included 1

#include <stdint.h>
#include "compiler.hpp"

extern "C" inline uint8_t inb(uint16_t port)
{
   uint8_t ret;
   asm volatile ("inb %0, %1" : "=a"(ret) : "Nd"(port));
   return ret;
}
extern "C" inline void outb(uint16_t port, uint8_t byte)
{
   asm volatile ("outb %1, %0" : : "a"(byte), "Nd"(port));
}

extern "C" inline void io_wait()
{
   // TODO: Find a really unused port
   outb(0x80, 0);
}

#endif
