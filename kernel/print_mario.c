#include "../drivers/screen.h"

#define RED_ON_WHITE 0x4f
#define BROWN_ON_WHITE 0x6f
#define YELLOW_ON_WHITE 0xef


void print_line(int rep, char attr) {
	for (int i = 0; i < rep; ++i) {
		print_char(' ', attr);
	}
}

void print_mario() {
    clear();

	set_cursor(get_screen_offset(0, 3));
	print_line(5, RED_ON_WHITE);

	set_cursor(get_screen_offset(1, 2));
	print_line(9, RED_ON_WHITE);

	set_cursor(get_screen_offset(2, 2));
	print_line(3, BROWN_ON_WHITE);
	print_line(2, YELLOW_ON_WHITE);
	print_line(1, BROWN_ON_WHITE);
	print_line(1, YELLOW_ON_WHITE);

	set_cursor(get_screen_offset(3, 1));
	print_line(1, BROWN_ON_WHITE);
	print_line(1, YELLOW_ON_WHITE);
	print_line(1, BROWN_ON_WHITE);
	print_line(3, YELLOW_ON_WHITE);
	print_line(1, BROWN_ON_WHITE);
	print_line(4, YELLOW_ON_WHITE);

	set_cursor(get_screen_offset(4, 1));
	print_line(1, BROWN_ON_WHITE);
	print_line(1, YELLOW_ON_WHITE);
	print_line(2, BROWN_ON_WHITE);
	print_line(3, YELLOW_ON_WHITE);
	print_line(1, BROWN_ON_WHITE);
	print_line(3, YELLOW_ON_WHITE);

	set_cursor(get_screen_offset(5, 1));
	print_line(2, BROWN_ON_WHITE);
	print_line(4, YELLOW_ON_WHITE);
	print_line(4, BROWN_ON_WHITE);
	
	set_cursor(get_screen_offset(6, 3));
	print_line(7, YELLOW_ON_WHITE);

	set_cursor(get_screen_offset(7, 2));
	print_line(2, BROWN_ON_WHITE);
	print_line(1, RED_ON_WHITE);
	print_line(3, BROWN_ON_WHITE);

	set_cursor(get_screen_offset(8, 1));
	print_line(3, BROWN_ON_WHITE);
	print_line(1, RED_ON_WHITE);
	print_line(2, BROWN_ON_WHITE);
	print_line(1, RED_ON_WHITE);
	print_line(3, BROWN_ON_WHITE);

	set_cursor(get_screen_offset(9, 0));
	print_line(4, BROWN_ON_WHITE);
	print_line(4, RED_ON_WHITE);
	print_line(4, BROWN_ON_WHITE);
	
	set_cursor(get_screen_offset(10, 0));
	print_line(2, YELLOW_ON_WHITE);
	print_line(1, BROWN_ON_WHITE);
	print_line(1, RED_ON_WHITE);
	print_line(1, YELLOW_ON_WHITE);
	print_line(2, RED_ON_WHITE);
	print_line(1, YELLOW_ON_WHITE);
	print_line(1, RED_ON_WHITE);
	print_line(1, BROWN_ON_WHITE);
	print_line(2, YELLOW_ON_WHITE);

	set_cursor(get_screen_offset(11, 0));
	print_line(3, YELLOW_ON_WHITE);
	print_line(6, RED_ON_WHITE);
	print_line(3, YELLOW_ON_WHITE);

	set_cursor(get_screen_offset(12, 0));
	print_line(2, YELLOW_ON_WHITE);
	print_line(8, RED_ON_WHITE);
	print_line(2, YELLOW_ON_WHITE);

	set_cursor(get_screen_offset(13, 2));
	print_line(3, RED_ON_WHITE);
	set_cursor(get_screen_offset(13, 7));
	print_line(3, RED_ON_WHITE);

	set_cursor(get_screen_offset(14, 1));
	print_line(3, BROWN_ON_WHITE);
	set_cursor(get_screen_offset(14, 8));
	print_line(3, BROWN_ON_WHITE);

	set_cursor(get_screen_offset(15, 0));
	print_line(4, BROWN_ON_WHITE);
	set_cursor(get_screen_offset(15, 8));
	print_line(4, BROWN_ON_WHITE);
}