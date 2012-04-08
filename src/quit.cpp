#include "quit.hpp"

#include "string.hpp"
#include "types.hpp"
#include "vga.hpp"

extern "C" void __attribute__ ((noreturn)) shutdown()
{
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
  u32 len = strlen(msg);
  u32 pos = (vga::max_i - len) / 2;

  vga::hide();
  vga::clear(vga::bg(vga::blue) | vga::fg(vga::white));
  vga::write(pos, msg);

  shutdown();
}
