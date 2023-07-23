#include "../drivers/screen.h"
// https://stackoverflow.com/questions/30552163/c-kernel-printing-string-not-working
// https://wiki.osdev.org/Printing_To_Screen
#include "./print_mario.h";

// Issues with printing/strings: currently able to only print 63 characters (excluding null byte)
// seems to be a memory limitation with how strings are being stored

void main() {
	clear();
	print_mario();

	const char msg[] = "Wrote my own VGA driver for my 32 bit OS";
	print_at(msg, 20, 20);
}