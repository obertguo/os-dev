;
; Simple boot sector program that includes a print function
;
[bits 16]
[org 0x7c00]    ; Set offset for where the boot program is loaded into memory

mov [BOOT_DRIVE], dl    ; BIOS stores our boot drive in DL on startup
                        ; so we'll need to remember this for later
mov dh, 2   ; DH stores the # of sectors we want to read/load into memory
            ; For now, let's read 2 sectors of the disk (each sector is 512B)
mov dl, [BOOT_DRIVE] ; select which drive to load (0 indexed)

mov bp, 0x8000 ; Set stack safely out of the way at 0x8000
mov sp, bp

mov bx, 0x0000  ; Indirectly set address to read sectors to
mov es, bx      ; by setting the starting segment
mov bx, 0x9000  ; Now, set the segment offset. 
                ; CPU translates this to 0x0000:0x9000 = 0x9000
call disk_load
call print_hex  ; Print hex value at mem addr of bx, where we read sectors to

jmp $

; IMPORTS
%include "print_hex.asm"
%include "print.asm"
%include "disk_load.asm"

; CONSTANTS
BOOT_DRIVE:
    db 0
my_str:
    db "test", 0

; Padding and magic number
times 510 - ($ - $$) db 0
dw 0xaa55

; Some dummy values to fill up 2 sectors
; Since each sector is usually 512 bytes
times 256 dw 0xdada
times 256 dw 0xface