[bits 16]
switch_pm:
    cli                     ; disable interrupts
    lgdt [gdt_descriptor]   ; load GDTR
    mov eax, cr0            ; To enable PM, lowest bit in CR0 needs to be set
    or eax, 0x1             ; We cannot write to CR0 directly so we use eax
    mov cr0, eax            ; We also use OR since there may be other bits 
                            ; set and used by the CPU

    jmp CODE_SEG:init_pm    ; make a far jump (i.e., to a new segment)
                            ; to our 32 bit code. This forces the CPU
                            ; to flush its cache of pre-fetched and real-mode
                            ; decoded instructions, which could cause problems.
                            ; The far jump also sets CS segment as well.

[bits 32]
; Initialize registers and stack once in PM
init_pm:
    mov ax, DATA_SEG    ; Now in PM, our old segments are meaningless
    mov ds, ax          ; so we update our segment registers to the
    mov ss, ax          ; data selector we defined in our GDT
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x9000     ; Update our stack position so it's at the top 
    mov esp, ebp        ; of the free space

    call begin_pm       ; Call some well known label