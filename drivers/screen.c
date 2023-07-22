#include "screen.h"
#include "../kernel/kernel_low_level.h"

// get_screen_offset(row, col) maps the row and col coordinates and
//      returns the memory offset for that character cell relative
//      to the start of the video memory
unsigned int get_screen_offset(unsigned int row, unsigned int col) {
    return 2 * (row * MAX_COLS + col);
}

// get_cursor returns the cursor position in video memory
int get_cursor() {
    int offset = 0;

    // The device uses the control register as an index
    //      to select its internal registers, which we are interested in
    //      I.e., the control register specifies which internal register 
    //      of the video hardware we wish to operate on
    //  - reg 14: high byte of cursor's offset
    //  - reg 15: low byte of cursor's offset

    // Read and store high byte
    port_byte_out(REG_SCREEN_CTRL, 14);
    offset = port_byte_in(REG_SCREEN_DATA) << 8;
    
    // Read low byte and add to offset
    port_byte_out(REG_SCREEN_CTRL, 15);
    offset += port_byte_in(REG_SCREEN_DATA);

    // Since cursor offset reported by VGA hardware is the 
    //      number of characters, we multiply by 2 to 
    //      convert it to video memory offset.
    return offset * 2;
}

// set_cursor(offset) sets the cursor position to 
//      the video memory offset location that is given
void set_cursor(int offset) {
    // convert video memory offset to character offset
    offset /= 2;

    //  - reg 14: high byte of cursor's offset
    //  - reg 15: low byte of cursor's offset

    // write high byte of cursor's offset
    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, (unsigned char) (offset >> 8));

    // write low byte of cursor's offset
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, (unsigned char) (offset));
}

// print_char(character, row, col, attribute_byte) prints the given
//      character to the screen at the specified col and row location,
//      with the given attribute style
void print_char(char character, int row, int col, char attribute_byte) {
    // byte pointer to start of video memory
    unsigned char *video_mem = (unsigned char *) VIDEO_ADDRESS;

    // set some basic styles
    if (!attribute_byte) {
        attribute_byte = WHITE_ON_BLACK;
    } else if (attribute_byte == 1) {
        attribute_byte = RED_ON_WHITE;
    } else if (attribute_byte == 2) {
        attribute_byte = GREEN_ON_BLACK;
    }
    
    // Get video memory offset for screen nlocation
    int offset = 0;

    // If col and row are non-negative, use them to calculate memory offset
    if (row >= 0 && col >= 0) {
        offset = get_screen_offset(row, col);
    
    // Otherwise, use the current cursoer position
    } else {
        offset = get_cursor();
    }

    // If we encounter a newline, set the offset to the end
    //      of the current row, so next char can be advanced 
    //      to the first col of the next row 
    if (character == '\n') {
        int rows = offset / (2 * MAX_COLS);
        offset = get_screen_offset(rows, MAX_COLS - 1);
    
    // Otherwise, write the character and attribute byte at the offset
    } else {
        video_mem[offset] = character;
        video_mem[offset + 1] = attribute_byte;
    }

    // Update the offset to the next character cell in memory 
    //      (2 bytes ahead of current)
    offset += 2;

    // TODO: implement this function
    //offset = handle_scrolling(offset);

    // Update cursor position to new offset
    set_cursor(offset);
}


// print_at(message, row, col) prints the given null terminated string message
//      at the given row and col location
void print_at(char* message, int row, int col) {
    if (row >= 0 && col >= 0) {
        int offset = get_screen_offset(row, col);
        set_cursor(offset);
    }


    int i = 0;
    while (message[i] != '\0') {
        print_char(message[i], row, col, 2);

        ++col; // move to next col 
        ++i;
    }
}

void print(char *message) {
    print_at(message, -1, -1);
}