;
; Simple boot sector program that enters 32 bit protected mode
;

[bits 16]
[org 0x7c00]                ; Set offset for where the boot program 
                            ; is loaded into memory
KERNEL_PHYSICAL_BASE equ 0x1000     ; Physical memory address that the kernel
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
    mov bx, KERNEL_PHYSICAL_BASE   
    
    mov dl, [BOOT_DRIVE]
    mov dh, 18              ; load 18 sectors of the disc (after bootloader) 
    call disk_load          ; into memory

    ret

[bits 32]
; Arrive here after switching to and initating 32 bit PM
begin_pm:
    mov ebx, MSG_PM_MODE
    call print_string_pm

    ; call fill_page_directory_table

    mov dword [PAGE_DIRECTORY_TABLE], 0x83              ; set up identity paging for first 4 MB of memory
    mov dword [PAGE_DIRECTORY_TABLE + 768 * 4], 0x83    ; entry 768 of the PDT corresponds to virtual address 0xC0000000 
                                                        ; which is the virtual address of the start of the kernel.
                                                        ; We map the first 4MB of this virtual kernel space to the first 4MB
                                                        ; of the physical address space
                                                        ; We need to set up a proper page table in our kernel code later
                                                        ; to properly reserve the upper 1GB of memory for the kernel
                                                        ; and initialize the remaining entries in the page table
                                                        ; and invalidate the identity page

    ; point cr3 to our filled in PDT
    mov eax, PAGE_DIRECTORY_TABLE
    mov cr3, eax

    ; since we have 4MB pages set up in our PDT
    ; we need to enable PSE (page size extenstion)
    mov eax, cr4
    or eax, 0x00000010
    mov cr4, eax

    ; now we can actually enable 32 bit paging
    ; by setting the paging (PG) and protection (PE) bits
    ; of cr0
    mov eax, cr0
    or eax, 0x80000001
    mov cr0, eax

    ; attempt to start in higher half now   ; https://stackoverflow.com/questions/52670384/instruction-after-paging-is-enabled-doesnt-appear-to-execute
    lea eax, [KERNEL_PHYSICAL_BASE]
    call eax            ; jump to address where the kernel is located
                        ; and hope for the best!!
    
    jmp $               ; Hang

; fill_page_directory_table:
;     pusha

;     mov ecx, 0                      ; loop counter index, we want to
;                                     ; run this loop 1024 times
;     mov eax, PAGE_DIRECTORY_TABLE   ; eax is a pointer to the page table
;                                     ; and stores our current entry position

;     pdt_loop_start: 
;         mov dword [eax], 0x83       ; set the entry in the PDT
;                                     ; 0x83 will map to the first 4 MB of 
;                                     ; physical memory, and indicate
;                                     ; a 4MB page size, the memory can only be 
;                                     ; accessed by the supervisor (kernel),
;                                     ; the page is writable, and the page
;                                     ; is present
;                                     ; https://wiki.osdev.org/Paging
;                                     ; https://medium.com/@connorstack/how-does-a-higher-half-kernel-work-107194e46a64
;                                     ; https://tldp.org/LDP/khg/HyperNews/get/devices/addrxlate.html

;         inc ecx                     ; increment loop count
;         add eax, 4                  ; increment eax to point to next table entry
;                                     ; as each entry is 4 bytes

;         cmp ecx, 1022               ; check to see if we are done 
;                                     ; filling in the 1024 entries
;         jne pdt_loop_start

;     popa
;     ret

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

; Allocate space for a 4 MB page directory table
; A page directory table has 1024 entries, each entry occupying 4 bytes
[bits 32]
section .bss
align 4096
PAGE_DIRECTORY_TABLE:
    resb 4096