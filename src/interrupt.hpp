#ifndef interrupt_hpp_included
#define interrupt_hpp_included 1

void load_interrupts();

#define ISR(n) void __attribute__ ((noreturn)) isr ## n ()
#define IRQ(n) void __attribute__ ((noreturn)) irq ## n ()

ISR(0);  // Divide Error
// isr1 is Intel-Reserved
ISR(2);  // NMI Interrupt
ISR(3);  // Breakpoint
ISR(4);  // Overflow
ISR(5);  // BOUND Range Excedeed
ISR(6);  // Invalid Opcode
ISR(7);  // No Math Coprocessor
ISR(8);  // Double Fault
ISR(9);  // Coprocessor Segment Overrun
ISR(10); // Invalid TSS
ISR(11); // Segment Not Present
ISR(12); // Stack-Segment Fault
ISR(13); // General Protection Exception (Triple Fault)
ISR(14); // Page Fault
// isr15 is Intel-Reserved
ISR(16); // Coprocessor Error
ISR(17); // Alignment Check
ISR(18); // Machine Check
ISR(19); // SIMD Floating-Point Exception

ISR(42); // Syscall

IRQ(0);
IRQ(1);
IRQ(2);
IRQ(3);
IRQ(4);
IRQ(5);
IRQ(6);
IRQ(7);
IRQ(8);
IRQ(9);
IRQ(10);
IRQ(11);
IRQ(12);
IRQ(13);
IRQ(14);
IRQ(15);

#endif
