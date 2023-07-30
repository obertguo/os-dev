// http://www.osdever.net/bkerndev/Docs/isrs.htm

#include "isrs.h"
#include "idt.h"
#include "../drivers/screen.h"

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

struct registers {
    unsigned int gs;        // pushed last
    unsigned int fs;
    unsigned int es;
    unsigned int ds;

    unsigned int edi;       // pushed by pusha
    unsigned int esi;
    unsigned int ebp;
    unsigned int esp;
    unsigned int ebx;
    unsigned int edx;
    unsigned int ecx;
    unsigned int eax;

    unsigned int int_no;    // pushed by us
    unsigned int err_code;  // pushed by processor or us

    unsigned int eip;       // pushed by processor when calling interrupt
    unsigned int cs;
    unsigned int eflags;
    unsigned int useresp;
    unsigned int ss;
} __attribute__((packed));


// isrs_install() sets the interrupt service routines in the IDT
void isrs_install() {
    idt_set_gate(0, &isr0, KERNEL_CODE_SEGMENT, FLAGS);
    idt_set_gate(1, &isr1, KERNEL_CODE_SEGMENT, FLAGS);
    idt_set_gate(2, &isr2, KERNEL_CODE_SEGMENT, FLAGS);
    idt_set_gate(3, &isr3, KERNEL_CODE_SEGMENT, FLAGS);
    idt_set_gate(4, &isr4, KERNEL_CODE_SEGMENT, FLAGS);
    idt_set_gate(5, &isr5, KERNEL_CODE_SEGMENT, FLAGS);
    idt_set_gate(6, &isr6, KERNEL_CODE_SEGMENT, FLAGS);
    idt_set_gate(7, &isr7, KERNEL_CODE_SEGMENT, FLAGS);
    idt_set_gate(8, &isr8, KERNEL_CODE_SEGMENT, FLAGS);
    idt_set_gate(9, &isr9, KERNEL_CODE_SEGMENT, FLAGS);
    idt_set_gate(10, &isr10, KERNEL_CODE_SEGMENT, FLAGS);
    idt_set_gate(11, &isr11, KERNEL_CODE_SEGMENT, FLAGS);
    idt_set_gate(12, &isr12, KERNEL_CODE_SEGMENT, FLAGS);
    idt_set_gate(13, &isr13, KERNEL_CODE_SEGMENT, FLAGS);
    idt_set_gate(14, &isr14, KERNEL_CODE_SEGMENT, FLAGS);
    idt_set_gate(15, &isr15, KERNEL_CODE_SEGMENT, FLAGS);
    idt_set_gate(16, &isr16, KERNEL_CODE_SEGMENT, FLAGS);
    idt_set_gate(17, &isr17, KERNEL_CODE_SEGMENT, FLAGS);
    idt_set_gate(18, &isr18, KERNEL_CODE_SEGMENT, FLAGS);
    idt_set_gate(19, &isr19, KERNEL_CODE_SEGMENT, FLAGS);
    idt_set_gate(20, &isr20, KERNEL_CODE_SEGMENT, FLAGS);
    idt_set_gate(21, &isr21, KERNEL_CODE_SEGMENT, FLAGS);
    idt_set_gate(22, &isr22, KERNEL_CODE_SEGMENT, FLAGS);
    idt_set_gate(23, &isr23, KERNEL_CODE_SEGMENT, FLAGS);
    idt_set_gate(24, &isr24, KERNEL_CODE_SEGMENT, FLAGS);
    idt_set_gate(25, &isr25, KERNEL_CODE_SEGMENT, FLAGS);
    idt_set_gate(26, &isr26, KERNEL_CODE_SEGMENT, FLAGS);
    idt_set_gate(27, &isr27, KERNEL_CODE_SEGMENT, FLAGS);
    idt_set_gate(28, &isr28, KERNEL_CODE_SEGMENT, FLAGS);
    idt_set_gate(29, &isr29, KERNEL_CODE_SEGMENT, FLAGS);
    idt_set_gate(30, &isr30, KERNEL_CODE_SEGMENT, FLAGS);
    idt_set_gate(31, &isr31, KERNEL_CODE_SEGMENT, FLAGS);
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