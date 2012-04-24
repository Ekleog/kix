#include <stdint.h>
#include "interrupt.hpp"
#include "multiboot.hpp"
#include "quit.hpp"
#include "vga.hpp"

// Suppress missing-declaration warning
extern "C" void __attribute__ ((noreturn)) kmain(multiboot *, uint32_t);
extern "C" void __attribute__ ((noreturn)) kmain(multiboot *mbd, uint32_t magic)
{
   if (magic != 0x2BADB002)
      panic("Invalid magic boot number.");

   vga::clear(vga::bg(vga::black) | vga::fg(vga::lgray));
   vga::write(vga::pos(1, 1), mbd->cmdline);
   vga::write(vga::pos(3, 1), mbd->boot_loader_name);
   vga::hide();

   load_interrupts();

   while (true) ;

   shutdown();
}
