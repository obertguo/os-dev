#ifndef UTIL_H
#define UTIL_H

// References
// https://www.ibiblio.org/gferg/ldp/GCC-Inline-Assembly-HOWTO.html
// http://www.jamesmolloy.co.uk/tutorial_html/3.-The%20Screen.html
// https://stackoverflow.com/questions/3215878/what-are-in-out-instructions-in-x86-used-for


// memory_copy(dest, src, no_bytes) copies the number of bytes from the 
//      destination to the src location
// Requires: src and dest are valid pointers, and no_bytes >= 0
void memory_copy(unsigned char *dest, 
    const unsigned char *src, unsigned int no_bytes);

// port_byte_in(port) reads and returns a byte 
//      from the given I/O port address
unsigned char port_byte_in(unsigned short port);

// port_byte_out(port, data) writes a byte of data to the given I/O port address
void port_byte_out(unsigned short port, unsigned char data);

// port_word_in(port) reads and returns a word
//      from the given I/O port address
unsigned char port_word_in(unsigned short port);

// port_word_out(port, data) writes a word of data to the given I/O port address
void port_word_out(unsigned short port, unsigned short data);

#endif