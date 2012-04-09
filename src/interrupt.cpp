#include "interrupt.hpp"

#include "idt.hpp"
#include "quit.hpp"
#include "vga.hpp"

void load_interrupts()
{
   init_idt();

   isr(0, isr0, 0);
   isr(2, isr2, 0);
   isr(3, isr3, 0);
   isr(4, isr4, 0);
   isr(5, isr5, 0);
   isr(6, isr6, 0);
   isr(7, isr7, 0);
   isr(8, isr8, 0);
   isr(9, isr9, 0);
   isr(10, isr10, 0);
   isr(11, isr11, 0);
   isr(12, isr12, 0);
   isr(13, isr13, 0);
   isr(14, isr14, 0);
   isr(16, isr16, 0);
   isr(42, isr42, 0);

   validate_idt();
}

#define ISR(n) void __attribute__ ((noreturn)) isr ## n ()
#define IBEGIN                \
   __asm__ volatile (         \
      "\t pusha \n"           \
      "\t push %gs \n"        \
      "\t push %fs \n"        \
      "\t push %ds \n"        \
      "\t push %es \n"        \
   )
#define IEND                  \
   __asm__ volatile (         \
      "\t pop %es \n"         \
      "\t pop %ds \n"         \
      "\t pop %fs \n"         \
      "\t pop %gs \n"         \
      "\t popa \n"            \
      "\t iret \n"            \
   );                         \
   __builtin_unreachable()

ISR(0) {
   IBEGIN;
   panic("Kernel panic: Divide Error");
   IEND;
}
ISR(2) {
   IBEGIN;
   panic("Kernel panic: NMI Interrupt");
   IEND;
}
ISR(3) {
   IBEGIN;
   panic("Kernel panic: Breakpoint");
   IEND;
}
ISR(4) {
   IBEGIN;
   panic("Kernel panic: Overflow");
   IEND;
}
ISR(5) {
   IBEGIN;
   panic("Kernel panic: BOUND Range Excedeed");
   IEND;
}
ISR(6) {
   IBEGIN;
   panic("Kernel panic: Invalid Opcode");
   IEND;
}
ISR(7) {
   IBEGIN;
   panic("Kernel panic: No Math Coprocessor");
   IEND;
}
ISR(8) {
   IBEGIN;
   panic("Kernel panic: Double Fault");
   IEND;
}
ISR(9) {
   IBEGIN;
   panic("Kernel panic: Coprocessor Segment Overrun");
   IEND;
}
ISR(10) {
   IBEGIN;
   panic("Kernel panic: Invalid TSS");
   IEND;
}
ISR(11) {
   IBEGIN;
   panic("Kernel panic: Segment Not Present");
   IEND;
}
ISR(12) {
   IBEGIN;
   panic("Kernel panic: Stack-Segment Fault");
   IEND;
}
ISR(13) {
   IBEGIN;
   panic("Kernel panic: General Protection (Triple Fault)");
   IEND;
}
ISR(14) {
   IBEGIN;
   panic("Kernel panic: Page Fault");
   IEND;
}
ISR(16) {
   IBEGIN;
   panic("Kernel panic: Coprocessor Error");
   IEND;
}
ISR(17) {
   IBEGIN;
   panic("Kernel panic: Alignment Check");
   IEND;
}
ISR(18) {
   IBEGIN;
   panic("Kernel panic: Machine Check");
   IEND;
}
ISR(19) {
   IBEGIN;
   panic("Kernel panic: SIMD Floating-Point Exception");
   IEND;
}

ISR(42) {
   IBEGIN;
   vga::clear(vga::bg(vga::black) | vga::fg(vga::lgray));
   vga::write(vga::pos(1, 1), "Syscall !");
   IEND;
}
