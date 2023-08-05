#ifndef PIT_H
#define PIT_H

// https://wiki.osdev.org/Programmable_Interval_Timer
// http://www.osdever.net/bkerndev/Docs/pit.htm

#define PIT_CHANNEL_0_DATA_PORT 0x40
#define PIT_CHANNEL_1_DATA_PORT 0x41
#define PIT_CHANNEL_2_DATA_PORT 0x42
#define PIT_COMMAND_REG 0x43

#define PIT_CLOCK_SPEED 1193180 // PIT runs at 1.19 MHz for historical reasons
// by default, the BIOS sets channel 0 with a count of 65535 or 0 
// (which translates to 65536)
// which gives an output frequency of 18.2065 Hz (or an IRQ every 54.9254 ms)

// Our own defined PIT clock frequency! 
// Set at 1000Hz for now so that the PIT fires IRQ0 every 1ms
#define PIT_HZ 1000 


// bits 6-7 - PIT channel select - we pick channel 0
// bits 4-5 - Access mode where 
//  0: latch count value command
//  1: acccess mode, lobyte only
//  2: access mode, hibyte only
//  3: access mode, lobyte/hibyte, which we pick
//      so we have to write lobyte first, then hibyte
// bits 1-3: operating mode - we pick mode 3 (110) for square wave 
//  this mode is the most common for BIOS and OS 
//  for PIT channel 0 IRQ0 timer ticks
#define PIT_CHANNEL_0_SQUARE_WAVE_CMD 0b00110110

// timer_install() sets up the PIT with the desired IRQ0 frequency and
//      installs the handler function into the IDT
void timer_install();

// sleep(ms) will delay current code execution for ms milliseconds
void sleep(const unsigned int ms);

#endif