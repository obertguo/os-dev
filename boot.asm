;
; Simple boot sector program that includes a print function
;

[org 0x7c00] ; Set offset for where the boot program is loaded into memory

; mov bx, my_string
; call my_print

; mov bx, my_string_2
; call my_print
mov bx, my_string
jmp print_hex
jmp $

%include "print.asm"
%include "print_hex.asm"

; DATA
my_string:
    db "Hello World!", 0
my_string_2:
    db " World", 0

; Padding and magic number
times 510 - ($ - $$) db 0
dw 0xaa55