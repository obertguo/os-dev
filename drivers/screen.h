#ifndef SCREEN_H
#define SCREEN_H

#define VIDEO_ADDRESS 0xC00B8000    // physical address is 0xb8000, but we are 
                                    // now using virtual memory where 
                                    // 0xC0008000 virtual maps to 
                                    // 0x00000000 physical
#define MAX_ROWS 25
#define MAX_COLS 80

// colors
#define BLACK 0x0
#define BLUE 0x1
#define GREEN 0x2
#define CYAN 0x3
#define RED 0x4
#define MAGENTA 0x5
#define BROWN 0x6
#define LIGHT_GRAY 0x7
#define DARK_GRAY 0x8
#define LIGHT_BLUE 0x9
#define LIGHT_GREEN 0xa
#define LIGHT_CYAN 0xb
#define LIGHT_RED 0xc
#define LIGHT_MAGENTA 0xd
#define YELLOW 0xe
#define WHITE 0xf

// Screen device I/O ports
#define REG_SCREEN_CTRL 0x3d4  
#define REG_SCREEN_DATA 0x3d5


// set_default_console_attribute(attribute_byte) sets the
//      attribute byte for the console
void set_default_console_attribute(unsigned char attribute_byte);


// generate_attribute_byte(fg, bg) returns an attribute byte to write to
//      the video memory with given forground color fg and background color bg
unsigned char generate_attribute_byte(unsigned char fg, unsigned char bg);


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

// print_char_attribs(c, attribute_byte) prints a character c at the current 
//      cursor position, and then advances the cursor position to the
//      next character cell. The styling is handed by attribute_byte 
//      The character can be ASCII printable, a newline (\n), or a 
//      backspace (\b)
// Requires: 
//      c is a printable character
//      attribute_byte is either 0, 1 or 2, or a byte for the VGA style to apply
void print_char_attrib(unsigned char c, unsigned char attribute_byte);

// print_char(c) prints the character c at the current cursor position
//      c can be an ASCII printable character, a newline (\n) or a 
//      backspace (\b)
void print_char(unsigned char c);

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

// clear() is self explanatory. It clears the screen.
void clear();

// printf(format, ...) is a custom implementation of the print format function
//      in the C standard library. Currently supports %s, %c, and %d
void printf(char *format, ...);

#endif