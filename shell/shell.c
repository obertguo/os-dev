#include "shell.h"
#include "../drivers/screen.h"
#include "../drivers/keyboard.h"

// start_shell() starts a new shell instance
void start_shell() {
    unsigned char input_buffer[INPUT_BUFFER_SIZE] = {0};
    unsigned char input_buffer_idx = 0;
    clear();
    
    print("Starting the OShell...\n");
    print("[OSh] >>");

    while (1) {
        unsigned char input_char = get_char();

        if (!input_char) {
            continue;
        }
       
        if (input_char == '\b') {
            if (input_buffer_idx > 0) {
                input_buffer[input_buffer_idx] = 0;
                --input_buffer_idx;

                print_char(input_char);
            }
        } else if (input_char == '\n') {
            print_newline();
            printf("Recieved command %s\n", input_buffer);
            print("[OSh] >>");

            input_buffer_idx = 0;
            for (unsigned char i = 0; i < INPUT_BUFFER_SIZE; ++i) {
                input_buffer[i] = 0;
            }
        } else {
            input_buffer[input_buffer_idx] = input_char;
            ++input_buffer_idx;

            print_char(input_char);
        }
    }
}
