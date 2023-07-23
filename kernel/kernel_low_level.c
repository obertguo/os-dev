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

void port_byte_out(unsigned short port, unsigned char data) {
    __asm__ volatile(
        "out %%al, %%dx"    // Assembler template, OUT writes to I/O device
        :
        : "a" (data), "d" (port)    // load EAX with data, load EDX with port
    );
}

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

void port_word_out(unsigned short port, unsigned short data) {
    __asm__ volatile(
        "out %%al, %%dx"    // Assembler template, OUT writes to I/O device
        :
        : "a" (data), "d" (port)    // load EAX with data, load EDX with port
    );
}


