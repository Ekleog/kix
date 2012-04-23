#include "quit.hpp"

#include <stdint.h>
#include "string.hpp"
#include "vga.hpp"

extern "C" void __attribute__ ((noreturn)) shutdown()
{
  // TODO: Call destructors
  __asm__ volatile (
      "\t cli \n"
      ".hang: \n"
      "\t hlt \n"
      "\t jmp .hang \n"
  );

  __builtin_unreachable();
}

extern "C" void __attribute__ ((noreturn)) panic(const char *msg)
{
  uint32_t len = strlen(msg);
  uint32_t pos = (vga::max_i - len) / 2;

  vga::hide();
  vga::clear(vga::bg(vga::blue) | vga::fg(vga::white));
  vga::write(pos, msg);

  shutdown();
}
