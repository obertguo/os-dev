#include "shell.h"
#include "../drivers/screen.h"
#include "../drivers/keyboard.h"

// start_shell() starts a new shell instance
void start_shell() {
    clear();
    print("SHELL >");

    while (1) {
        unsigned char *input = get_line();
        if (input) {
            print_newline();
            printf("Recieved command %s\n", input);
            print("SHELL >");
        }
    }
}