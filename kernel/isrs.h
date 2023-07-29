#ifndef ISRS_H
#define ISRS_H

#define KERNEL_CODE_SEGMENT 0x08
#define FLAGS 0b10001110

void isrs_install();
void fault_handler();

#endif