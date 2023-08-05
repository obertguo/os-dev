// http://www.osdever.net/bkerndev/Docs/isrs.htm

#include "isrs.h"
#include "../idt/idt.h"
#include "../../../drivers/screen.h"

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();
extern void isr31();

const char *exception_messages[] = {
    "Division By Zero",
    "Debug Exception", 
    "Non Maskable Interrupt Exception",
    "Breakpoint Exception",
    "Into Detected Overflow Exception",
    "Out of Bounds Exception",
    "Invalid Opcode Exception",
    "No Coprocessor Exception",
    "Double Fault Exception",
    "Coprocessor Segment Overrun Exception",
    "Bad TSS Exception",
    "Segment Not Present Exception",
    "Stack Fault Exception",
    "General Protection Fault Exception",
    "Page Fault Exception",
    "Unknown Interrupt Exception",
    "Coprocessor Fault Exception",
    "Alignment Check Exception (486+)",
    "Machine Check Exception (Pentium/586+)",
    "Reserved 19",
    "Reserved 20",
    "Reserved 21",
    "Reserved 22",
    "Reserved 23",
    "Reserved 24",
    "Reserved 25",
    "Reserved 26",
    "Reserved 27",
    "Reserved 28",
    "Reserved 29",
    "Reserved 30",
    "Reserved 31"
};

void *isr_routines[] = {
    isr0, isr1, isr2, isr3, isr4, isr5, isr6, isr7,
    isr8, isr9, isr10, isr11, isr12, isr13, isr14, isr15,
    isr16, isr17, isr18, isr19, isr20, isr21, isr22, isr23,
    isr24, isr25, isr26, isr27, isr28, isr29, isr30, isr31
};

// isrs_install() sets the interrupt service routines in the IDT
void isrs_install() {
    // Install first 32 ISRs for exceptions
    for (unsigned char i = 0; i < 32; ++i) {
        idt_set_gate(i, isr_routines[i], KERNEL_CODE_SEGMENT, FLAGS);
    }
}

// fault_handler(r) handles interrupt exceptions from 0 to 31 by
//      printing the exception message and then hangs.
// Requires: r is a valid pointer to a stack with register values pushed onto it
//          when invoked by a function in our isr_handler 
void fault_handler(const struct registers *r) {
    // Check if the interrupt number is from 0 to 32
    if (r && r->int_no < 32) {
        print("System Halted - Exception Raised! ");
        print(exception_messages[r->int_no]);

        for (;;) {} // Hang forever
    }
}