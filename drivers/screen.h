#ifndef SCREEN_H
#define SCREEN_H

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80

// Attribute byte
#define WHITE_ON_BLACK 0x0f
#define GREEN_ON_BLACK 0xa0
#define RED_ON_WHITE 0x4f

// Screen device I/O ports
#define REG_SCREEN_CTRL 0x3d4   // This 
#define REG_SCREEN_DATA 0x3d5


// get_screen_offset(row, col) maps the row and col coordinates and
//      returns the memory offset for that character cell relative
//      to the start of the video memory
unsigned int get_screen_offset(unsigned int row, unsigned int col);

// set_cursor(offset) sets the cursor position to 
//      the video memory offset location that is given
void set_cursor(unsigned int offset);

// print_line(count, attribute_byte) prints a space/blank character count 
//      number of times at the current cursor position. It is styles
//      with the given attribute_byte
// Requires: count >= 0 and attribute_byte is a valid styling
void print_line(unsigned int count, unsigned char attrribute_byte);

// print_newline() advances the current cursor position to the
//      start of the next line
void print_newline();

// print_char(c, attribute_byte) prints a character c at the current 
//      cursor position, and then advances the cursor position to the
//      next character cell. The styling is handed by attribute_byte 
// Requires: 
//      c is a printable character
//      attribute_byte is either 0, 1 or 2, or a byte for the VGA style to apply
void print_char(unsigned char c, unsigned char attribute_byte);

// print_at(message, row, col) prints the given null terminated string 
//      str at the given row and col location
// Requires: 
//      0 <= row < MAX_ROW
//      0 <= col < MAX_COL
//      str is a valid pointer to a null terminated string
void print_at(const char str[], unsigned int row, unsigned int col);

// print(str) prints the null terminated string str at the current 
//      cursor location.
// Requires:
//      str is a valid pointer to a null terminated string
void print(const char str[]);

void clear();

#endif