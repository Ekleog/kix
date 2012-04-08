#include "quit.hpp"
#include "types.hpp"
#include "vga.hpp"

// Suppress missing-declaration warning
extern "C" void __attribute__ ((noreturn)) kmain(byte *, u32);
extern "C" void __attribute__ ((noreturn)) kmain(byte *mbd, u32 magic)
{
   if (magic != 0x2BADB002)
      panic("Invalid magic boot number.");

   char *cmdline          = *(reinterpret_cast<char **>(mbd + 16));
   char *boot_loader_name = *(reinterpret_cast<char **>(mbd + 64));

   vga::clear(vga::bg(vga::black) | vga::fg(vga::lgray));
   vga::write(vga::pos(1, 1), cmdline);
   vga::write(vga::pos(3, 1), boot_loader_name);
   vga::hide();

   shutdown();
}
