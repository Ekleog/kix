#include "interrupt.hpp"

#include "idt.hpp"
#include "pic.hpp"
#include "quit.hpp"
#include "vga.hpp"

void load_interrupts()
{
   pic::remap();
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

   isr(0x50, irq0, 0);
   isr(0x51, irq1, 0);
   isr(0x52, irq2, 0);
   isr(0x53, irq3, 0);
   isr(0x54, irq4, 0);
   isr(0x55, irq5, 0);
   isr(0x56, irq6, 0);
   isr(0x57, irq7, 0);
   isr(0x58, irq8, 0);
   isr(0x59, irq9, 0);
   isr(0x5a, irq10, 0);
   isr(0x5b, irq11, 0);
   isr(0x5c, irq12, 0);
   isr(0x5d, irq13, 0);
   isr(0x5e, irq14, 0);
   isr(0x5f, irq15, 0);

   validate_idt();
}

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
   panic("Kernel panic: General Protection Exception (Triple Fault)");
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

IRQ(0) {
   IBEGIN;
   IEND;
}
IRQ(1) {
   IBEGIN;
   IEND;
}
IRQ(2) {
   IBEGIN;
   IEND;
}
IRQ(3) {
   IBEGIN;
   IEND;
}
IRQ(4) {
   IBEGIN;
   IEND;
}
IRQ(5) {
   IBEGIN;
   IEND;
}
IRQ(6) {
   IBEGIN;
   IEND;
}
IRQ(7) {
   IBEGIN;
   IEND;
}
IRQ(8) {
   IBEGIN;
   IEND;
}
IRQ(9) {
   IBEGIN;
   IEND;
}
IRQ(10) {
   IBEGIN;
   IEND;
}
IRQ(11) {
   IBEGIN;
   IEND;
}
IRQ(12) {
   IBEGIN;
   IEND;
}
IRQ(13) {
   IBEGIN;
   IEND;
}
IRQ(14) {
   IBEGIN;
   IEND;
}
IRQ(15) {
   IBEGIN;
   IEND;
}
