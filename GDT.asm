[bits 16]
; GDT flat memory model
; each descriptor occupies 8 bytes
gdt_start:
    gdt_null:
        dd 0x0  ; Mandatory null descriptor
        dd 0x0  ; Needs to occupy 8 zero bytes
                ; Is necessary as protection
    gdt_code:   ; Code segment descriptor
    ; http://www.independent-software.com/operating-system-development-protected-mode-global-descriptor-table.html
    ; https://wiki.osdev.org/Global_Descriptor_Table
    
    ; base: 0x0 and limit: 0xfffff
    ; Access Byte (8 bits)
        ; present: 1
            ; since the segment is present in memory
            ; must be 1 for any valid segment
        ; privilege 00 (2 bits)
            ; where ring 0 is highest privilege
        ; descriptor type: 1
            ; where 1 is for code or data segment
            ; and 0 is for traps
        ; TYPE FLAGS (lowest 4 bit in Access Byte)
            ; executable: 1
                ; If set to 0, descriptor defines a data segment
                ; that cannot be executed from
                ; If set to 1, descriptor defines a code segment
                ; that can be executed from
            ; conforming: 0
                ; where 0 indicates the code can only
                    ; be executed from the privilege level indicated 
                    ; in the privilege flag. If 1, then the code can be 
                    ; executed from lower privilege levels
            ; readable (for code segment): 1
                ; where 1 indicates contents of memory can be written to
            ; accessed: 0
                ; the CPU will set this to 1 when the segment is accessed
                ; initially, we can set this to 0 
    ; Flags (4 bits)
        ; granularity: 1, 
            ; if set to 0, then descriptor's limit is specified 
            ; in 1 byte blocks (byte granularity)
            ; If set to 1, then it's specified in 4KB blocks/pages (page granularity)
            ; I.e., multiplies our limit by 4K (16^3)  
            ; E.g., Our limit 0xfffff would become 0xfffff000
            ; (similar to shifting 3 hex digits to the left)
            ; This allows our segment ot span 4GB of memory
            ; We'd like to access full 4GB of memory, so
            ; we set this to 1. 
        ; size: 1
            ; 1 indicates 32 bit protected mode
            ; A value of 0 indicates 16 bit protected mode
        ; Long mode/64 bit segment: 0 
            ; if set to 1, the descriptor defines a 64 bit code segment
            ; Since we are working with 32 bit, we'll set it to 0
        ; AVL: 0 
            ; we can set this for our own uses (e.g., debugging) 
            ; but we will not use it. It's a reserved flag 
            ; that is ignored by hardware

        ;;;;;;;;;;;;;;;;;;;
        dw 0xffff       ; Limit (first 16 bits), bit 0-15
        dw 0x0000       ; Base (first 16 bits), bit 16-31
        db 0x00         ; Base (next 8 bits), bit 32-39
        db 10011010b    ; Access Type (8 bits), bit 40-47
        db 11001111b    ; lowest 4 bits are next 4 bits of the Limit (bit 48-51)
                        ; highest 4 bits are Flags (bit 52-55)
        db 0x00         ; Base (last 8 bits), bit 56-63
        ;;;;;;;;;;;;;;;;;;;

    gdt_data:   ; data segment descriptor
                ; same as code segment, except for Type flag in Access Byte
    ; TYPE FLAGS
        ; executable: 0 (since this is a data segment)
        ; direction (for data segments): 0
            ; A valud of 0 indicated the segment grows up
            ; A value of 1 indicates the segment grows down (limit < offset)
        ; writable: 1, indicating write access to data segment
        ; accessed: 0 (default, CPU will set this automatically)
        ;;;;;;;;;;;;;;;;;;;
        dw 0xffff       ; Limit (first 16 bits), bit 0-15
        dw 0x0000       ; Base (first 16 bits), bit 16-31
        db 0x00         ; Base (next 8 bits), bit 32-39
        db 10010010b    ; Access Type (8 bits), bit 40-47
        db 11001111b    ; lowest 4 bits are next 4 bits of the Limit (bit 48-51)
                        ; highest 4 bits are Flags (bit 52-55)
        db 0x00         ; Base (last 8 bits), bit 56-63
        ;;;;;;;;;;;;;;;;;;;
    gdt_end:    ; Reason for having a label at the end of the GDT
                ; is so we can have the assembler calculate
                ; the size of the GDT for the GDT Descriptor
; GDT Descriptor (GDTR) - 48 bits long
; Lower 16 bits is for the size of GDT
; Upper 32 bits is for the starting address of the GDT
gdt_descriptor:
    dw gdt_end - gdt_start - 1  ; Size of our GDT, always needs to be 1 less
    dd gdt_start                ; Start address of GDT


; Define useful constants for GDTR offsets
; which are what segment registers must contain when we
; are in protected mode. E.g., if we set DS = 0x10 in PM
; the CPU knows that we mean to use the segment described 
; at offset 0x10 (byte 16) in our GDT, which in our case is the DATA segment
;(0x0 -> NULL   ; 0x08 -> CODE ; 0x10 -> DATA)
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start