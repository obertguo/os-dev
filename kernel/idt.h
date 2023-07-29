#ifndef IDT_H
#define IDT_H

#define NUM_IDT_ENTRIES 256

void idt_install();
void idt_set_gate(unsigned char num, unsigned int base, 
                    unsigned short selector, unsigned char flags);

#endif