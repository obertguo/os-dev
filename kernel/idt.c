// References:
// https://wiki.osdev.org/Interrupt_Descriptor_Table
// http://www.osdever.net/bkerndev/Docs/idt.htm

#include "idt.h"
#include "../drivers/screen.h"
#include "isrs.h"
#include "irq.h"

// Define an IDT entry
// Each IDT entry is 8 bytes
struct idt_entry {
    unsigned short base_lo; // low address of entry point of ISR
    unsigned short selector;// kernel segment goes here, must point to valid 
                            //      code segment in GDT
    unsigned char always0;  // always set to 0, reserved

    unsigned char flags;    // From lowest to highest bit:
                            // Gate Type: 4 bit value that defines 
                            //      the type of gate the Interrupt Descriptor 
                            //      represents. There are 5 types
                            // DPL: A 2 bit value that defines CPU privilege 
                            //      levels that are allowed to access this 
                            //      interrupt using INT instruction
                            //      Hardware interrupts ignore this
                            // P: Present bit. Must be set to 1 for 
                            //      the descriptor to be valid 


    unsigned short base_hi; // high address of entry point of ISR
} __attribute__((packed));  // avoid compiler padding

// Used to load IDT when we call lidt in assembly
// Must be 6 bytes
struct idt_ptr {
    unsigned short limit;   // limit is 2 bytes, size of IDT array - 1
    unsigned int base;      // base is 4 bytes, pointer to IDT array
} __attribute__((packed));


// IDT can contain up to 256 entries, so lets declare that
// We will use the first 32 entries, the rest exist as a bit of a trap
// If any undefined IDT entry is hit, it normally will cause
// an "Unhandled Interrupt" exception. Any descriptor
// for which the Present bit is cleared (0) will generate
// an "Unhandled Interrupt" exception

struct idt_entry idt[NUM_IDT_ENTRIES] = {0};
struct idt_ptr idtp = {};

// idt_load() is an inline assembly function to load our newly created IDT
// Note: we could've chosen to implement ldt_load externally in a 
//          separate assembly file, but we could also do it inline in C...
// https://stackoverflow.com/questions/56424988/gcc-inline-assembly-error-invalid-instruction-suffix-for-lidt
void idt_load() {
    __asm__ volatile (
        "lidt %0" 
        :
        : "m" (idtp)    // memory constraint, http://www.ibiblio.org/gferg/ldp/GCC-Inline-Assembly-HOWTO.html#ss6.1
    );
}

// enable_interrupt() sets the interrupt flag after interrupts have been cleared
// This is just a formal way to initialize interrupts after IDT is installed
void enable_interrupt() {
    __asm__ volatile(
        "sti" : :
    );
}

// idt_set_gate(num, base, selector, flags) sets an entry in
//      the IDT. Num specifies the entry number in the IDT, base specifies the 
//      memory address of the function to invoke for this interrupt
//      and selector and flags sets the corresponding fields for the IDT entry
void idt_set_gate(unsigned char num, void *(base)(void), 
                    unsigned short selector, unsigned char flags) {

    const unsigned int func = (unsigned int) base;
    unsigned short base_lo = func & 0x0000ffff;
    unsigned short base_hi = (func >> 16) & 0x0000ffff;

    idt[num].base_lo = base_lo;
    idt[num].base_hi = base_hi;
    idt[num].always0 = 0;
    idt[num].selector = selector;
    idt[num].flags = flags;
}

// idt_install() sets up the interrupt descriptor table
void idt_install() {
    idtp.limit = (sizeof(struct idt_entry) * NUM_IDT_ENTRIES) - 1;
    idtp.base = (unsigned int) &idt;

    // clear IDT and initizlie to all 0s
    for (int i = 0; i < NUM_IDT_ENTRIES; ++i) {
        idt[i].base_lo = 0;
        idt[i].base_hi = 0;
        idt[i].always0 = 0;
        idt[i].selector = 0;
        idt[i].flags = 0;
    }

    // Install interrupt service routines, which are interrupts 0 to 31
    isrs_install();
    irq_install();

    // Install any user defined ISRs to the IDT here

    // Load the IDT
    idt_load();

    // Call sti instruction to enable interrupts
    enable_interrupt();
}