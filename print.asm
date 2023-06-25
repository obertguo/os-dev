print_string:
    ; bx stores mem address of null terminated string, used as incremental ptr
     
    pusha ; push all general purpose registers onto the stack

    print_string_start:
        mov ah, 0x0e
        mov al, [bx]
        cmp al, 0
        je print_string_done

        add bx, 1
        int 0x10

        jmp print_string_start

    print_string_done:
        popa ; restore general purpose registers
        ret ; return to next line of code

print_char:
    ; dl stores char to print
    pusha

    mov ah, 0x0e
    mov al, dl 
    int 0x10

    popa
    ret