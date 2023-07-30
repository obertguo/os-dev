#ifndef ISRS_H
#define ISRS_H

#define KERNEL_CODE_SEGMENT 0x08
#define FLAGS 0b10001110

// register values pushed onto the stack - defined in isrs.c file
struct registers;

// isrs_install() sets the interrupt service routines in the IDT
void isrs_install();

// fault_handler(r) handles interrupt exceptions from 0 to 31 by
//      printing the exception message and then hangs.
// Requires: r is a valid pointer to a stack with register values pushed onto it
//          when invoked by a function in our isr_handler 
void fault_handler(const struct registers *r);

#endif