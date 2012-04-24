#include "interrupt.hpp"

#include "compiler.hpp"
#include "idt.hpp"
#include "pic.hpp"
#include "quit.hpp"
#include "asm.hpp"
#include "vga.hpp"

#define ISRN(n)   isr ## n
#define SCN(n)    sc  ## n
#define IRQN(n)   irq ## n

#define ISRD(n)   extern "C" void ISRN(n) ()
#define SCD(n)    extern "C" void SCN(n)  ()
#define IRQD(n)   extern "C" void IRQN(n) ()

#define IB(n)                          \
   asm volatile (                      \
      ".extern impl_" n "  \n"         \
      ".global " n "       \n"         \
      "" n ":              \n"         \
      "\t pushad           \n"         \
      "\t call impl_" n "  \n"         \
      "\t popad            \n"         \
      "\t iretd            \n"         \
   );

// TODO: Remove noreturn
#define ISR(n) IB("isr" #n)            \
   extern "C" void __attribute__ ((noreturn)) impl_isr ## n ();   \
   extern "C" void impl_isr ## n ()
#define SC(n)  IB("sc"  #n)            \
   extern "C" void impl_sc  ## n ();   \
   extern "C" void impl_sc  ## n ()
#define IRQ(n)                         \
   asm volatile (                      \
      ".extern impl_irq" #n " \n"      \
      ".global irq" #n "      \n"      \
      "irq" #n ":             \n"      \
      "\t pushad              \n"      \
      "\t call impl_irq" #n " \n"      \
      "\t mov al, 0x20        \n"      \
      "\t out 0x20, al        \n"      \
      "\t popad               \n"      \
      "\t iretd               \n"      \
   );                                  \
   extern "C" void impl_irq ## n ();   \
   extern "C" void impl_irq ## n ()
#define IRQ2(n)                        \
   asm volatile (                      \
      ".extern impl_irq" #n " \n"      \
      ".global irq" #n "      \n"      \
      "irq" #n ":             \n"      \
      "\t pushad              \n"      \
      "\t call impl_irq" #n " \n"      \
      "\t mov al, 0x20        \n"      \
      "\t out 0xA0, al        \n"      \
      "\t out 0x20, al        \n"      \
      "\t popad               \n"      \
      "\t iretd               \n"      \
   );                                  \
   extern "C" void impl_irq ## n ();   \
   extern "C" void impl_irq ## n ()

ISRD(0x00); ISRD(0x01); ISRD(0x02); ISRD(0x03);
ISRD(0x04); ISRD(0x05); ISRD(0x06); ISRD(0x07);
ISRD(0x08); ISRD(0x09); ISRD(0x0a); ISRD(0x0b);
ISRD(0x0c); ISRD(0x0d); ISRD(0x0e); // 0x0f reserved
ISRD(0x10); ISRD(0x11); ISRD(0x12); ISRD(0x13);
// reserved up to 0x1f

SCD(0x20);

IRQD(0x50); IRQD(0x51); IRQD(0x52); IRQD(0x53);
IRQD(0x54); IRQD(0x55); IRQD(0x56); IRQD(0x57);
IRQD(0x58); IRQD(0x59); IRQD(0x5a); IRQD(0x5b);
IRQD(0x5c); IRQD(0x5d); IRQD(0x5e); IRQD(0x5f);

void load_interrupts()
{
   using idt::isr;

   pic::remap();
   idt::init();

   isr(0x00, ISRN(0x00), 0);
   // isr0x01
   isr(0x02, ISRN(0x02), 0);
   isr(0x03, ISRN(0x03), 0);
   isr(0x04, ISRN(0x04), 0);
   isr(0x05, ISRN(0x05), 0);
   isr(0x06, ISRN(0x06), 0);
   isr(0x07, ISRN(0x07), 0);
   isr(0x08, ISRN(0x08), 0);
   isr(0x09, ISRN(0x09), 0);
   isr(0x0a, ISRN(0x0a), 0);
   isr(0x0b, ISRN(0x0b), 0);
   isr(0x0c, ISRN(0x0c), 0);
   isr(0x0d, ISRN(0x0d), 0);
   isr(0x0e, ISRN(0x0e), 0);
   // isr0x0f
   isr(0x10, ISRN(0x10), 0);
   isr(0x11, ISRN(0x11), 0);
   isr(0x12, ISRN(0x12), 0);
   isr(0x13, ISRN(0x13), 0);

   isr(0x20, SCN(0x20), 0);

   //isr(0x50, IRQN(0x50), 0);
   isr(0x51, IRQN(0x51), 0);
   /*isr(0x52, IRQN(0x52), 0);
   isr(0x53, IRQN(0x53), 0);
   isr(0x54, IRQN(0x54), 0);
   isr(0x55, IRQN(0x55), 0);
   isr(0x56, IRQN(0x56), 0);
   isr(0x57, IRQN(0x57), 0);
   isr(0x58, IRQN(0x58), 0);
   isr(0x59, IRQN(0x59), 0);
   isr(0x5a, IRQN(0x5a), 0);
   isr(0x5b, IRQN(0x5b), 0);
   isr(0x5c, IRQN(0x5c), 0);
   isr(0x5d, IRQN(0x5d), 0);
   isr(0x5e, IRQN(0x5e), 0);
   isr(0x5f, IRQN(0x5f), 0);*/

   idt::validate();
}

// ISRs

ISR(0x00) {
   panic("Kernel panic: Divide Error");
}

ISR(0x01) {
   panic("Kernel panic: Debug");
}

ISR(0x02) {
   panic("Kernel panic: NMI Interrupt");
}

ISR(0x03) {
   panic("Kernel panic: Breakpoint");
}

ISR(0x04) {
   panic("Kernel panic: Overflow");
}

ISR(0x05) {
   panic("Kernel panic: BOUND Range Excedeed");
}

ISR(0x06) {
   panic("Kernel panic: Invalid Opcode");
}

ISR(0x07) {
   panic("Kernel panic: No Math Coprocessor");
}

ISR(0x08) {
   panic("Kernel panic: Double Fault");
}

ISR(0x09) {
   panic("Kernel panic: Coprocessor Segment Overrun");
}

ISR(0x0a) {
   panic("Kernel panic: Invalid TSS");
}

ISR(0x0b) {
   panic("Kernel panic: Segment Not Present");
}

ISR(0x0c) {
   panic("Kernel panic: Stack-Segment Fault");
}

ISR(0x0d) {
   panic("Kernel panic: General Protection Exception (Triple Fault)");
}

ISR(0x0e) {
   panic("Kernel panic: Page Fault");
}

// 0x0f reserved

ISR(0x10) {
   panic("Kernel panic: Coprocessor Error");
}

ISR(0x11) {
   panic("Kernel panic: Alignment Check");
}

ISR(0x12) {
   panic("Kernel panic: Machine Check");
}

ISR(0x13) {
   panic("Kernel panic: SIMD Floating-Point Exception");
}

// reserved up to 0x1f

// SCs

SC(0x20) {
   vga::clear(vga::bg(vga::black) | vga::fg(vga::lgray));
   vga::write(vga::pos(1, 1), "Syscall !");
}

// IRQs

/*
IRQ(0x50) {
}
*/

uint32_t i = vga::pos(5, 1);
IRQ(0x51) {
   uint8_t c = inb(0x60);
   static char trans[] = "??1234567890-=??qwertyuiop[]??asdfghjkl;'`??zxcvbnm,./?*? ?????????????789-456+1230.??";
   vga::write(i, trans[c]);
   ++i;
}

/*
IRQ(0x52) {
}

IRQ(0x53) {
}

IRQ(0x54) {
}

IRQ(0x55) {
}

IRQ(0x56) {
}

IRQ(0x57) {
}

IRQ2(0x58) {
}

IRQ2(0x59) {
}

IRQ2(0x5a) {
}

IRQ2(0x5b) {
}

IRQ2(0x5c) {
}

IRQ2(0x5d) {
}

IRQ2(0x5e) {
}

IRQ2(0x5f) {
}
*/
