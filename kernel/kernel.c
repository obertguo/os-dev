#include "../drivers/screen.h"
#include "idt.h"
// https://stackoverflow.com/questions/30552163/c-kernel-printing-string-not-working
// https://wiki.osdev.org/Printing_To_Screen

#include "./print_mario.h"

void call_int();

void main() {
	idt_install();
	clear();

	print_mario();
	int a = 5 / 0;
	// call_int();

	// clear();
	// print_mario();

	// char str[] = "1234567890";

	// const char msg[] = "The C kernel is working, and so is the VGA driver!";
	// const char msg2[] = "testing......";
	// const char msg3[] = "Hello world";

	// print_newline();
	// print(msg);
	// print_newline();
	// print(msg2);
	// print_newline();
	// print(msg3);

	// print_at(msg, 20, 20);
	// set_cursor(get_screen_offset(24, 79));

	// print_char('T', RED_ON_WHITE);
	// print(msg3);
}

void call_int() {
	__asm__ volatile (
		"int %0" 
		: 
		: "i" (31)
	);
}