// https://www.win.tue.nl/~aeb/linux/kbd/scancodes-10.html
// https://wiki.osdev.org/PS/2_Keyboard
// http://www-ug.eecg.toronto.edu/msl/nios_devices/datasheets/PS2%20Keyboard%20Protocol.htm
// http://www.osdever.net/bkerndev/Docs/keyboard.htm

#include "keyboard.h"
#include "../kernel/util.h"
#include "../kernel/interrupts/irq/irq.h"
#include "../kernel/interrupts/isrs/isrs.h"
#include "screen.h"
#include "../kernel/util.h"

// scancode to ASCII mapping table
const unsigned char scancode_set_1_US[128];

// Store inputs
unsigned char char_pressed = 0;

// Flags for special keyboard keys for when they are pressed
unsigned char LEFT_SHIFT_DOWN = 0;
unsigned char RIGHT_SHIFT_DOWN = 0;
unsigned char CAPS_LOCK_ON = 0;

// keyboard_set_scancode(scancode) sets the keyboard controller to use
//      the scancode set scancode.
void keyboard_set_scancode(enum SET_KEYBOARD_SCANCODES scancode) {
    port_byte_out(KEYBOARD_PORT, GET_SET_SCANCODE_CMD);
	port_byte_out(KEYBOARD_PORT, scancode);
}

// keyboard_get_scancode() returns the keyboard scancode set being used
unsigned char keyboard_get_scancode() {
    port_byte_out(KEYBOARD_PORT, GET_SET_SCANCODE_CMD);
	port_byte_out(KEYBOARD_PORT, GET_SCANCODE);

    unsigned char scancode = port_byte_in(KEYBOARD_PORT);

    switch (scancode) {
        case GET_SCANCODE_1:
            print("Keyboard set to scancode 1\n");
            break;
        case GET_SCANCODE_2:
            print("Keyboard set to scancode 2\n");
            break;
        case GET_SCANCODE_3:
            print("Keyboard set to scancode 3\n");
            break;
        default:
            print("Unknown scancode\n");
            break;
    }
    
    return scancode;
}

// keyboard_set_led(led) sets the LED state on the keyboard
void keyboard_set_led(enum SET_KEYBOARD_LEDS led) {
    port_byte_out(KEYBOARD_PORT, SET_LED_CMD);
	port_byte_out(KEYBOARD_PORT, led);
}

// print_key(r) handles keyboard IRQ1 and prints the key that was pressed
//      if the key is ASCII printable.
// Requires: r is a valid pointer to register values on the stack, invoked by
//      the IRQ handler
void print_key(const struct registers *r) {
    unsigned char scancode = port_byte_in(KEYBOARD_PORT);
    if (scancode == RESPONSE_KEYBOARD_ACK ||
        scancode == RESPONSE_ECHO) {

    } else if (scancode == RESPONSE_KEY_ERROR_1 ||
                scancode == RESPONSE_KEY_ERROR_2 ||
                scancode == RESPONSE_SELF_TEST_FAILED_1 ||
                scancode == RESPONSE_SELF_TEST_FAILED_2) {
        
        print("Keyboard Error!");

    } else if (scancode == RESPONSE_KEYBOARD_RESEND) {
        print("Keyboard interrupted with a RESEND response");

    // Scancode starting at 0x80 and higher can indicate key releases
    } else if (scancode & 0x80) {
        
        // Retrieve the key that is released using XOR and our lookup table
        unsigned char c = scancode_set_1_US[scancode ^ 0x80];

        if (c == LEFT_SHIFT) {
            LEFT_SHIFT_DOWN = 0;
        } else if (c == RIGHT_SHIFT){
            RIGHT_SHIFT_DOWN = 0;
        }


    // Else, a key is pressed, and we'll get multiple key press interrupts
    // if its held down
    } else {
        // for now, we will just print the key to console
        // we can add some more checks later for Ctl, Alt, Shift keys, etc
        // or use larger lookup table

        unsigned char c = scancode_set_1_US[scancode];

        // ASCII printable, 
        if (' ' <= c && c <= '~') {

            // Handle caps lock logic
            if (CAPS_LOCK_ON) {
                if ('a' <= c && c <= 'z') {
                    c -= 'a' - 'A';
                }
            }

            // Handle shift logic
            if (LEFT_SHIFT_DOWN ^ RIGHT_SHIFT_DOWN) {
                if ('a' <= c && c <= 'z') {
                    c -= 'a' - 'A';
                } else if ('0' <= c && c <= '9') {
                    unsigned char lookup[] = {')', '!', '@', '#', '$', '%', 
                                                '^', '&', '*', '('};
                    c = lookup[c - '0'];
                } else {
                    switch (c) {
                        case '`':
                            c = '~';
                            break;
                        case '-':
                            c = '_';
                            break;
                        case '=':
                            c = '+';
                            break;
                        case '[':
                            c = '{';
                            break;
                        case ']':
                            c = '}';
                            break;
                        case '\\':
                            c = '|';
                            break;
                        case ';':
                            c = ':';
                            break;
                        case '\'':
                            c = '\"';
                            break;
                        case ',':
                            c = '<';
                            break;
                        case '.':
                            c = '>';
                            break;
                        case '/':
                            c = '?';
                            break; 
                        default:
                            break;
                    }
                }
            }
            
            char_pressed = c;
        
        // Backspace or Enter keys
        } else if (c == '\b' || c == '\n') {
            char_pressed = c;
        
        // Set flags for special keys
        } else if (c == LEFT_SHIFT) {
            LEFT_SHIFT_DOWN = 1;
        } else if (c == RIGHT_SHIFT){
            RIGHT_SHIFT_DOWN = 1;
        } else if (c == CAPS_LOCK) {
            CAPS_LOCK_ON = !CAPS_LOCK_ON;

        // Non-printable keys or other special keys not implemented
        } else {
            print("Not printable");
        }
    }
}

// get_char() returns a char containing the character inputted
//      since the last interrupt 
//      Otherwise, if no recent interrrupts occured, it returns 0
unsigned char get_char() {
    if (char_pressed) {
        char c = char_pressed;
        char_pressed = 0;

        return c;
    } else {
        return 0;
    }
}

// keyboard_install() sets up keyboard IRQ1 for use in the IDT 
void keyboard_install() {
    irq_install_handler(1, print_key);
}


// scancode to ASCII mapping table
const unsigned char scancode_set_1_US[128] = {
    0,  27 /* Escape */, '1', '2', '3', '4', '5', '6', '7', '8', '9',   // entry 0x0a - 10
    '0', '-', '=', '\b' /* Backspace */, '\t' /* Tab */,                // entry 0x0f - 15 
    'q', 'w', 'e', 'r',	't', 'y', 'u', 'i', 'o', 'p', '[', ']',         // entry 0x1b - 27
    '\n' /* Enter key */, 0 /* Left Control */,                         // entry 0x1d - 29
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',        // entry 0x29 - 41
    LEFT_SHIFT, '\\', 'z', 'x', 'c', 'v', 'b', 'n',                     // entry 0x31 - 
    'm', ',', '.', '/',   RIGHT_SHIFT,                                  // entry 0x36
    '*' /* Keypad * */, 0 /* Left Alt */,                               // entry 0x38
    ' '/* Space bar */, CAPS_LOCK,                                      // entry 0x3a
    
    0,	/* F1 key ... > */                                              // entry 0x3b - 59
    0,   0,   0,   0,   0,   0,   0,   0,                               // entry 0x3c to 0x43
    0,	/* < ... F10 */                                                 // entry 0x44 - 68

    /* Keypad keys ... > */
    0,	/* Num lock*/                                                   // entry 0x45 - 69
    0,	/* Scroll Lock */                                               // entry 0x46 - 70
    0,	/* Home key */                                                  // entry 0x47 - 71
    0,	/* Up Arrow */                                                  // entry 0x48 - 72
    0,	/* Page Up */                                                   // entry 0x49 - 73
    '-',                                                                // entry 0x4a - 74
    0,	/* Left Arrow */                                                // entry 0x4b - 75
    0,                                                                  // entry 0x4c - 76 
    0,	/* Right Arrow */                                               // entry 0x4d - 77
    '+',                                                                // entry 0x4e - 78
    0,	/* 79 - End key*/                                               // entry 0x4f - 79
    0,	/* Down Arrow */                                                // entry 0x50 - 80
    0,	/* Page Down */                                                 // entry 0x51 - 81
    0,	/* Insert Key */                                                // entry 0x52 - 82
    0,	/* Delete Key */                                                // entry 0x53 - 83
    0,   0,   0 /* These 3 are undefined and will never be sent */,     // entry 0x54 to 0x56
    0,	/* F11 Key */                                                   // entry 0x57 - 87
    0,	/* F12 Key */                                                   // entry 0x58 - 88
    0,	/* Some other keys are undefined and rest are for key releases */
};	