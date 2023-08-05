#include "screen.h"
#include "../kernel/util.h"
#include "../kernel/util.h"

// get_screen_offset(row, col) maps the row and col coordinates and
//      returns the memory offset for that character cell relative
//      to the start of the video memory
unsigned int get_screen_offset(unsigned int row, unsigned int col) {
    return 2 * (row * MAX_COLS + col);
}

// get_cursor returns the cursor position in video memory
unsigned int get_cursor() {
    unsigned int offset = 0;

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
void set_cursor(unsigned int offset) {
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

// print_line(count, attribute_byte) prints a space/blank character count 
//      number of times at the current cursor position. It is styles
//      with the given attribute_byte
// Requires: count >= 0 and attribute_byte is a valid styling
void print_line(unsigned int count, unsigned char attribute_byte) {
	for (unsigned int i = 0; i < count; ++i) {
		print_char(' ', attribute_byte);
	}
}

// handle_scrolling() scrolls the VGA buffer to the next line
void handle_scrolling() {
    // to handle scrolling, we can copy over the next row to the current row
    unsigned int current_row = 0;
    unsigned int next_row = 1;

    unsigned char *current_row_addr = 0;
    unsigned char *next_row_addr = 0;

    for (int i = 0; i < MAX_ROWS - 1; ++i) {
        current_row_addr = (unsigned char *) 
                            (VIDEO_ADDRESS + get_screen_offset(current_row, 0));
        next_row_addr = (unsigned char *) 
                            (VIDEO_ADDRESS + get_screen_offset(next_row, 0));

        memory_copy(current_row_addr, next_row_addr, MAX_COLS * 2);

        ++current_row;
        ++next_row;
    }

    // reset/clear the last line by writing 
    //      0s to the last line in VGA buffer
    // Note that if we used the print_line function function, which uses
    //      the print_char function, we get into a bad recursive loop...
    //      So we avoid it by intervening and 
    //      clearing without using a helper function.
    unsigned char *video_mem = (unsigned char *) VIDEO_ADDRESS + 
                                get_screen_offset(MAX_ROWS - 1, 0);

    for (int i = 0; i < 2 * MAX_COLS; ++i) {
        *(video_mem + i) = 0;
    }

    // set cursor to the start of the last line
    set_cursor(get_screen_offset(MAX_ROWS - 1, 0));
}

// print_newline() advances the current cursor position to the
//      start of the next line
void print_newline() {
    unsigned int offset = get_cursor();
    unsigned int current_row = offset / (2 * MAX_COLS);

    // determine the location of the last character cell in the current row
    offset = get_screen_offset(current_row, MAX_COLS - 1);

    // advance the offset to the next character cell
    //      which will be the next line
    offset += 2;

    // update cursor position
    set_cursor(offset);
}

// print_char(c, attribute_byte) prints a character c at the current 
//      cursor position, and then advances the cursor position to the
//      next character cell. The styling is handed by attribute_byte 
// Requires: 
//      c is a printable character
//      attribute_byte is the VGA style to apply
void print_char(unsigned char c, unsigned char attribute_byte) {

     // Get video memory offset for cursor location
    unsigned int offset = get_cursor();

    // byte pointer to start of video memory
    unsigned char *video_mem = (unsigned char *) VIDEO_ADDRESS;

    // Handle newline
    if (c == '\n') {
        print_newline();

    // Otherwise, print character at current offset position
    } else {
        video_mem[offset] = c;
        video_mem[offset + 1] = attribute_byte;

        // advance offset to the next character cell
        offset += 2;

        // If the offset exceeds the VGA buffer, we need to "scroll"
        if (offset > get_screen_offset(MAX_ROWS - 1, MAX_COLS - 1)) {
            handle_scrolling();

            // Otherwise, update the cursor position to the updated offset
        } else {
            set_cursor(offset);
        }
    }
}


// print(str) prints the null terminated string str at the current 
//      cursor location.
// Requires:
//      str is a valid pointer to a null terminated string
void print(const char str[]) {
    unsigned int i = 0;

    while (str[i] != '\0') {
        print_char(str[i], GREEN_ON_BLACK);
        ++i;
    }
}

// print_at(message, row, col) prints the given null terminated string 
//      str at the given row and col location
// Requires: 
//      0 <= row < MAX_ROW
//      0 <= col < MAX_COL
//      str is a valid pointer to a null terminated string
void print_at(const char str[], unsigned int row, unsigned int col) {
    unsigned int offset = get_screen_offset(row, col);
    set_cursor(offset);

    unsigned int i = 0;
    while (str[i] != '\0') {
        print_char(str[i], RED_ON_WHITE);
        ++i;
    }
}

// clear() clears the VGA screen 
void clear() {
    // We can clear the screen by overwriting the VGA buffer with spaces

    // Set cursor to the start of the screen (top-left)
    set_cursor(0);

    // Overwrite VGA buffer with spaces
    // The cursor automatically advances to the next character cell
    for (unsigned int row = 0; row < MAX_ROWS; ++row) {
        print_line(MAX_COLS, WHITE_ON_BLACK);
    }

    // Restore cursor position to the start of the VGA buffer (top-left)
    set_cursor(0);
}