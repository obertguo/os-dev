disk_load:
    pusha
    push dx ; DH contains # of sectors to read
    ; DL contains which drive to read from
    ; push value of DX onto stack to use for comparison later (compare DH)
    ; and since we are in 16 bit mode, we can only push DX and not DH

    ; mov ah, 0x0e
    ; mov al, dl
    ; add al, '0'
    ; int 0x10

    mov ah, 0x02 ; BIOS interrupt for reading 

    mov al, dh ; set number of sectors to read

    mov ch, 0x00 ; select cylinder 0 
    mov dh, 0x00 ; select track/head 0 (0 indexed)
    mov cl, 0x02 ; start reading from 2nd sector (1 indexed)
    
    int 0x13 ; BIOS interrupt for disk read

    jc disk_read_err ; jc = jump carry, jump if carry flag is set (read error)

    pop dx      ; restore dx to contain # sectors read
    cmp al, dh  ; AL is set to # of sectors read after calling disk read
                ; So, check if # sectors read matches what we expect
    
    jne disk_read_incomplete
    
    popa
    ret
disk_read_err:
    mov bx, DISK_READ_ERR_MSG
    call print_string
    jmp $
disk_read_incomplete:
    mov bx, DISK_READ_INCOMPLETE_MSG
    call print_string
    jmp $

DISK_READ_ERR_MSG:
    db "Disk read failed!", 0
DISK_READ_INCOMPLETE_MSG:
    db "Disk read incomplete!", 0