;
; Simple boot sector program that enters 32 bit protected mode
;

[bits 16]
[org 0x7c00]                ; Set offset for where the boot program 
                            ; is loaded into memory
KERNEL_OFFSET equ 0x1000    ; Memory offset for which the kernel
                            ; will be loaded from

    xor ax, ax              ; Reset DS register
    mov ds, ax

    mov [BOOT_DRIVE], dl    ; DL will always contain the boot drive 
                            ; when BIOS starts. Save for later

    mov bp, 0x9000          ; Set up the stack
    mov sp, bp

    call load_kernel

    mov bx, MSG_REAL_MODE   ; Announce we are moving from 16 bit real mode
    call print_string       ; to 32 bit protected mode

    call switch_pm          ; Note: we never return from here

; IMPORTS
%include "print_hex.asm"
%include "print.asm"
%include "disk_load.asm"
%include "GDT.asm"
%include "switch_PM.asm"

[bits 16]
; LOAD KERNEL
load_kernel:
    mov bx, MSG_LOAD_KERNEL
    call print_string

    mov bx, 0x00            ; specify memory address to load kernel to
    mov es, bx              ; using es:bx offset
    mov bx, KERNEL_OFFSET   
    
    mov dl, [BOOT_DRIVE]
    mov dh, 18              ; load 18 sectors of the disc (after bootloader) 
    call disk_load          ; into memory

    ret

[bits 32]
; Arrive here after switching to and initating 32 bit PM
begin_pm:
    mov ebx, MSG_PM_MODE
    call print_string_pm

    mov ecx, 0
    mov eax, PAGE_TABLE

    PDT_FILL:
        mov ebx, 0x0
        or ebx, 0x83
        mov [eax], ebx

        inc ecx
        add eax, 4

        cmp ecx, 4096
        jne PDT_FILL

    mov eax, PAGE_TABLE
    mov cr3, eax

    mov eax, cr4
    or eax, 0x00000010
    mov cr4, eax

    mov eax, cr0
    or eax, 0x80000001
    mov cr0, eax

    lea eax, [KERNEL_OFFSET]
    call eax  ; jump to address where the kernel is located
                        ; and hope for the best!!
    
    jmp $               ; Hang

[bits 16]
; Global Variables
MSG_REAL_MODE:
    db "Entering 32 bit protected mode...", 0
MSG_PM_MODE:
    db "RUNNING IN 32 BIT PROTECTED MODE", 0
MSG_LOAD_KERNEL:
    db "Loading C Kernel...", 0
BOOT_DRIVE:
    db 0

; Padding and magic number
times 510 - ($ - $$) db 0
dw 0xaa55

[bits 32]
section .bss
align 4096
PAGE_TABLE:
    resb 4096
;
; section .data
; align 4096
; PAGE_TABLE
;     times 1024 dd 0x83
