#ifndef IDT_H
#define IDT_H

#define NUM_IDT_ENTRIES 256

// idt_install() sets up the interrupt descriptor table
void idt_install();

// idt_set_gate(num, base, selector, flags) sets an entry in
//      the IDT. Num specifies the entry number in the IDT, base specifies the 
//      memory address of the function to invoke for this interrupt
//      and selector and flags sets the corresponding fields for the IDT entry
void idt_set_gate(unsigned char num, void *(base)(), 
                    unsigned short selector, unsigned char flags);

#endif