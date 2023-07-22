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

// print_char(character, row, col, attribute_byte) prints the given
//      character to the screen at the specified col and row location,
//      with the given attribute style
void print_char(char character, int row, int col, char attribute_byte);

// print_at(message, row, col) prints the given null terminated string message
//      at the given row and col location
void print_at(char* message, int row, int col);

// void print(char *message) prints a message to the screen at the current
//      cursor position.
void print(char *message);

#endif