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

	//some stuff
	clear();
	print_mario();
	sleep(200);
	clear();
	
	start_shell();
	
	// call_int();
}

void call_int() {
	__asm__ volatile (
		"int %0" 
		: 
		: "i" (32)
	);
}