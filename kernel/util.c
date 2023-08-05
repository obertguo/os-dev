// memory_copy(src, dest, no_bytes) copies the number of bytes from the 
//      destination to the src location
// Requires: src and dest are valid pointers, and no_bytes >= 0
void memory_copy(unsigned char *src, const unsigned char *dest, 
    unsigned int no_bytes) {
    
    for (unsigned int i = 0; i < no_bytes; ++i) {
        *(src + i) = *(dest + i);
    }
}

// port_byte_in(port) reads and returns a byte 
//      from the given I/O port address
unsigned char port_byte_in(unsigned short port) {
    unsigned char result = 0;
    __asm__ volatile(
        "in %%dx, %%al"     //  Assembler template, IN reads from I/O device
        :  "=a" (result)    //  Output operands (optional), variable result 
                            //      will store AL register
        : "d" (port)        //  Input operarands (optional), load EDX with port
    );      
    return result;
}

// port_byte_out(port, data) writes a byte of data to the given I/O port address
void port_byte_out(unsigned short port, unsigned char data) {
    __asm__ volatile(
        "out %%al, %%dx"    // Assembler template, OUT writes to I/O device
        :
        : "a" (data), "d" (port)    // load EAX with data, load EDX with port
    );
}

// port_word_in(port) reads and returns a word
//      from the given I/O port address
unsigned char port_word_in(unsigned short port) {
    unsigned char result = 0;
    __asm__ volatile (
        "in %%dx, %%al"     //  Assembler template, IN reads from I/O device
        :  "=a" (result)    //  Output operands (optional), variable result 
                            //      will store AL register
        : "d" (port)        //  Input operarands (optional), load EDX with port
    );      
    return result;
}

// port_word_out(port, data) writes a word of data to the given I/O port address
void port_word_out(unsigned short port, unsigned short data) {
    __asm__ volatile(
        "out %%al, %%dx"    // Assembler template, OUT writes to I/O device
        :
        : "a" (data), "d" (port)    // load EAX with data, load EDX with port
    );
}


