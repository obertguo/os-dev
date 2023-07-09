;
; Simple boot sector program that enters 32 bit protected mode
;

[bits 16]
[org 0x7c00]    ; Set offset for where the boot program is loaded into memory

    xor ax, ax
    mov ds, ax

    mov bp, 0x9000  ; Set the stack
    mov sp, bp

    mov bx, MSG_REAL_MODE
    call print_string

    call switch_pm  ; Note: we never return from here

; IMPORTS
%include "print_hex.asm"
%include "print.asm"
; %include "disk_load.asm"
%include "GDT.asm"
%include "switch_PM.asm"

[bits 32]
; Arrive here after switching to and initating 32 bit PM
begin_pm:
    mov ebx, MSG_PM_MODE
    call print_string_pm
    jmp $

[bits 16]
; Global Variables
MSG_REAL_MODE:
    db "Entering 32 bit protected mode...", 0
MSG_PM_MODE:
    db "RUNNING IN 32 BIT PROTECTED MODE", 0

; Padding and magic number
times 510 - ($ - $$) db 0
dw 0xaa55

; Some dummy values to fill up 2 sectors
; Since each sector is usually 512 bytes
times 256 dw 0xdada
times 256 dw 0xface