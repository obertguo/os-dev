#ifndef KEYBOARD_H
#define KEYBOARD_H

#define KEYBOARD_PORT 0x60

#define RESPONSE_KEYBOARD_ACK 0xfa
#define RESPONSE_KEYBOARD_RESEND 0xfe

#define GET_SET_SCANCODE_CMD 0xf0
#define GET_SCANCODE 0x0

#define GET_SCANCODE_1 0x43
#define GET_SCANCODE_2 0x41
#define GET_SCANCODE_3 0x3f

enum SET_KEYBOARD_SCANCODES {
    SCANCODE_1 = 1,
    SCANCODE_2 = 2,
    SCANCODE_3 = 3
};

// keyboard_install() sets up keyboard IRQ1 for use in the IDT 
void keyboard_install();

// keyboard_set_scancode(scancode) sets the keyboard controller to use
//      the scancode set scancode.
void keyboard_set_scancode(enum SET_KEYBOARD_SCANCODES scancode);

// keyboard_get_scancode() returns the keyboard scancode set being used
unsigned char keyboard_get_scancode();

#endif