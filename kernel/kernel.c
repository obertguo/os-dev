#include "../drivers/screen.h"
#include "interrupts/idt/idt.h"
#include "../drivers/pit.h"
#include "../drivers/keyboard.h"
#include "../shell/shell.h"
// https://stackoverflow.com/questions/30552163/c-kernel-printing-string-not-working
// https://wiki.osdev.org/Printing_To_Screen

#include "./print_mario.h"

void call_int();

void main() {
	// First, install IRQ routines
	timer_install();
	keyboard_install();

	// Then install IDT
	idt_install();

	set_default_console_attribute(generate_attribute_byte(BLUE, WHITE));

	clear();

	// Next, initialize keyboard to use scancode set 2 (usually is the default)
	//		But, since keyboard output is fed to a 8042 microprocessor
	//		the scancode gets translated back into scancode set 1
	//		This is due to compatibility reasons
	keyboard_set_scancode(SCANCODE_2);
	keyboard_get_scancode();

	//some stuff
	clear();
	sleep(500);
	print_mario();
	sleep(500);
	clear();
	
	start_shell();
	
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
		: "i" (32)
	);
}