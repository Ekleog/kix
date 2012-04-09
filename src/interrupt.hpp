#ifndef interrupt_hpp_included
#define interrupt_hpp_included 1

void load_interrupts();

void isr0();   // Divide Error
// isr1 is Intel-Reserved
void isr2();   // NMI Interrupt
void isr3();   // Breakpoint
void isr4();   // Overflow
void isr5();   // BOUND Range Excedeed
void isr6();   // Invalid Opcode
void isr7();   // No Math Coprocessor
void isr8();   // Double Fault
void isr9();   // Coprocessor Segment Overrun
void isr10();  // Invalid TSS
void isr11();  // Segment Not Present
void isr12();  // Stack-Segment Fault
void isr13();  // General Protection (Triple Fault)
void isr14();  // Page Fault
// isr15 is Intel-Reserved
void isr16();  // Coprocessor Error
void isr17();  // Alignment Check
void isr18();  // Machine Check
void isr19();  // SIMD Floating-Point Exception

void isr42();  // Syscall

#endif
