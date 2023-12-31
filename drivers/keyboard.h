#ifndef KEYBOARD_H
#define KEYBOARD_H

#define KEYBOARD_PORT 0x60

#define RESPONSE_KEYBOARD_ACK 0xfa
#define RESPONSE_KEYBOARD_RESEND 0xfe
#define RESPONSE_KEY_ERROR_1 0x00
#define RESPONSE_KEY_ERROR_2 0xff
#define RESPONSE_SELF_TEST_FAILED_1 0xfc
#define RESPONSE_SELF_TEST_FAILED_2 0xfd
#define RESPONSE_ECHO 0xee

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

#define SET_LED_CMD 0xed

enum SET_KEYBOARD_LEDS {
    SCROLL_LOCK = 0,
    NUMBER_LOCK = 1,
    CAPS_LOCK = 2
};

// keyboard_install() sets up keyboard IRQ1 for use in the IDT 
void keyboard_install();

// keyboard_set_scancode(scancode) sets the keyboard controller to use
//      the scancode set scancode.
void keyboard_set_scancode(enum SET_KEYBOARD_SCANCODES scancode);

// keyboard_get_scancode() returns the keyboard scancode set being used
unsigned char keyboard_get_scancode();

// keyboard_set_led(led) sets the LED state on the keyboard
void keyboard_set_led(enum SET_KEYBOARD_LEDS led);

// get_char() returns a char containing the character inputted
//      since the last interrupt 
//      Otherwise, if no recent interrrupts occured, it returns 0
unsigned char get_char();

#define LEFT_SHIFT 240
#define RIGHT_SHIFT 241
#define CAPS_LOCK 242

#endif