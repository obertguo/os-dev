[bits 16]
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

[bits 16]
print_char:
    ; dl stores char to print
    pusha

    mov ah, 0x0e
    mov al, dl 
    int 0x10

    popa
    ret

[bits 32]
 ; Define some constants
VIDEO_MEM equ 0xb8000
WHITE_ON_BLACK equ 0x0f
WHITE_ON_BLUE equ 0x9f
print_string_pm:
    ; print a null-terminated string pointed by ebx
    pusha
    mov edx, VIDEO_MEM

    print_string_pm_start:
        mov al, [ebx]
        mov ah, WHITE_ON_BLUE

        cmp al, 0
        je print_string_pm_done

        mov [edx], ax

        add ebx, 1
        add edx, 2

        jmp print_string_pm_start

    print_string_pm_done:
        popa
        ret