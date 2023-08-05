#include "keyboard.h"
#include "../kernel/util.h"
#include "../kernel/interrupts/irq/irq.h"
#include "../kernel/interrupts/isrs/isrs.h"
#include "screen.h"

void *get_scancode(const struct registers *r) {

    int scan = port_byte_in(KEYBOARD_PORT);

    port_byte_out(KEYBOARD_PORT, GET_SET_SCAN_CODE_CMD);
    port_byte_out(KEYBOARD_PORT, 0);

    scan = port_byte_in(KEYBOARD_PORT);
    if (scan == 0x43) {
        print("Scan code 1");
    } else if (scan == 0x41) {
        print("Scan code 1");
    } else if (scan == 0x3f) {
        print("Scan code 1");
    } else if (scan == 0xFA) {
        print("ACK");
    }
}

void keyboard_install() {
    irq_install_handler(1, get_scancode);
}