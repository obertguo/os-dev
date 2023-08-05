#include "pit.h"
#include "../kernel/interrupts/isrs/isrs.h"
#include "../kernel/interrupts/irq/irq.h"
#include "../kernel/util.h"
#include "screen.h"

unsigned int timer_ticks = 0;

// set_timer_phase(hz) sets how many times per second the PIT should send IRQ0
// requires: 0 <= hz <= 2^16
void set_timer_phase(unsigned int hz) {
    // PIT supports 16 bit so we use short, and use this calculation to obtain
    //  a scaling factor that we write to the PIT channel 0 data port
    //  so that we set the appropriate PIT clock speed 
    unsigned short divisor = PIT_CLOCK_SPEED / hz;

    port_byte_out(PIT_COMMAND_REG, PIT_CHANNEL_0_SQUARE_WAVE_CMD);

    unsigned char lobyte = divisor & 0x00ff;
    unsigned char hibyte = divisor >> 8;

    // PIT data port supports only 8 bits, so send lobyte first and then hibyte
    port_byte_out(PIT_CHANNEL_0_DATA_PORT, lobyte);
    port_byte_out(PIT_CHANNEL_0_DATA_PORT, hibyte);
}

// timer_handler(r) is the IRQ0 handler that needs to be installed
//      to set up PIT
// Requires: r is a valid pointer to register values on the stack, called
//          by our IRQ handler function 
void *timer_handler(const struct registers *r) {
    ++timer_ticks;

    if (timer_ticks % PIT_HZ == 0) {
        print("\nOne second has passed");
    }
}

// timer_install() sets up the PIT with the desired IRQ0 frequency and
//      installs the handler function into the IDT
void timer_install() {
    set_timer_phase(PIT_HZ);
    irq_install_handler(0, timer_handler);
}