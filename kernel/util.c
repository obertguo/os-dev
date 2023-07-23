// memory_copy(src, dest, no_bytes) copies the number of bytes from the 
//      destination to the src location
// Requires: src and dest are valid pointers, and no_bytes >= 0
void memory_copy(unsigned char *src, const unsigned char *dest, 
    unsigned int no_bytes) {
    
    for (unsigned int i = 0; i < no_bytes; ++i) {
        *(src + i) = *(dest + i);
    }
}