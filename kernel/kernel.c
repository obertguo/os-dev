#include "../drivers/screen.h"
// https://stackoverflow.com/questions/30552163/c-kernel-printing-string-not-working
// https://wiki.osdev.org/Printing_To_Screen

void main() {
	const char str[] = "The C kernel is working, and so is the VGA driver!";
	const char str2[] = "\nWe can also print a new line!";

	print(str);
	print(str2);
}