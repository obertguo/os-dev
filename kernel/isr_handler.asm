; http://www.osdever.net/bkerndev/Docs/isrs.htm

[extern fault_handler]     ; Let compiler know that _fault_handler will be
                            ; implemented later in our C code
global isr0                ; Needed so that this function symbol is exported
                            ; for the linker so that when our C code calls this 
                            ; function, it gets resolved to this function that
                            ; we implemented here - like a header file of sorts.
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31

; We have an isr_common_stub function that saves the processor state on 
;   on the stack, push the current stack address onto the stack
;   (gives our C handler the stack), call our C fault_handler function
;   and finally restore the state of the stack

isr_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs

    mov ax, 0x10        ; Load our Kernel data segment descriptor
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    mov eax, esp        ; push the stack memory address into eax
    push eax            ; as that is going to be passed as a pointer argument
                        ; when we call our fault_handler function in C

    mov eax, fault_handler
    call eax            ; a special call, preserves the EIP register

    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa

    add esp, 8          ; Clean up the pushed error code and pushed ISR number
    iret                ; pops 5 entries at once, CS, EIP, EFLAGS, SS, and ESP.
                        ; Returns to the caller function that issued the 
                        ; the interrupt. This instruction differs from RET

; ISR 0: Divide by Zero Exception
isr0:
    cli                 ; Clear/disable interrupts to prevent another IRQ from firing
                        ; which could possibly cause conflicts in our kernel
    push byte 0         ; A normal ISR stub that pops a dummy error code 
                        ; to keep a uniform stack frame
    push byte 0         ; To track which interrupt is fired
    jmp isr_common_stub

; ISR 1: Debug Exception
isr1:
    cli                 ; Clear/disable interrupts to prevent another IRQ from firing
                        ; which could possibly cause conflicts in our kernel
    push byte 0         ; A normal ISR stub that pops a dummy error code 
                        ; to keep a uniform stack frame
    push byte 1         ; To track which interrupt is fired
    jmp isr_common_stub

; ISR 2: Non Maskable Interrupt Exception
isr2:
    cli                 ; Clear/disable interrupts to prevent another IRQ from firing
                        ; which could possibly cause conflicts in our kernel
    push byte 0         ; A normal ISR stub that pops a dummy error code 
                        ; to keep a uniform stack frame
    push byte 2         ; To track which interrupt is fired
    jmp isr_common_stub

; ISR 3: Breakpoint Exception
isr3:
    cli                 ; Clear/disable interrupts to prevent another IRQ from firing
                        ; which could possibly cause conflicts in our kernel
    push byte 0         ; A normal ISR stub that pops a dummy error code 
                        ; to keep a uniform stack frame
    push byte 3         ; To track which interrupt is fired
    jmp isr_common_stub

; ISR 4: Into Detected Overflow Exception
isr4:
    cli                 ; Clear/disable interrupts to prevent another IRQ from firing
                        ; which could possibly cause conflicts in our kernel
    push byte 0         ; A normal ISR stub that pops a dummy error code 
                        ; to keep a uniform stack frame
    push byte 4         ; To track which interrupt is fired
    jmp isr_common_stub

; ISR 5: Out of Bounds Exception
isr5:
    cli                 ; Clear/disable interrupts to prevent another IRQ from firing
                        ; which could possibly cause conflicts in our kernel
    push byte 0         ; A normal ISR stub that pops a dummy error code 
                        ; to keep a uniform stack frame
    push byte 5         ; To track which interrupt is fired
    jmp isr_common_stub

; ISR 6: Invalid Opcode Exception
isr6:
    cli                 ; Clear/disable interrupts to prevent another IRQ from firing
                        ; which could possibly cause conflicts in our kernel
    push byte 0         ; A normal ISR stub that pops a dummy error code 
                        ; to keep a uniform stack frame
    push byte 6         ; To track which interrupt is fired
    jmp isr_common_stub

; ISR 7: No Coprocessor Exception
isr7:
    cli                 ; Clear/disable interrupts to prevent another IRQ from firing
                        ; which could possibly cause conflicts in our kernel
    push byte 0         ; A normal ISR stub that pops a dummy error code 
                        ; to keep a uniform stack frame
    push byte 7         ; To track which interrupt is fired
    jmp isr_common_stub

; ISR 8: Double Fault Exception (With Error Code)
isr8:
    cli                 ; Clear/disable interrupts to prevent another IRQ from firing
                        ; which could possibly cause conflicts in our kernel
    push byte 8         ; Note that we DON'T push a value on the stack
                        ; in this one. It pushes one already. Use this type
                        ; of stub for exceptions that pop error codes.
    jmp isr_common_stub ; To track which interrupt is fired

; ISR 9: Coprocessor Segment Overrun Exception
isr9:
    cli                 ; Clear/disable interrupts to prevent another IRQ from firing
                        ; which could possibly cause conflicts in our kernel
    push byte 0         ; A normal ISR stub that pops a dummy error code 
                        ; to keep a uniform stack frame
    push byte 9         ; To track which interrupt is fired
    jmp isr_common_stub

; ISR 10: Bad TSS Exception (With Error Code)
isr10:
    cli                 ; Clear/disable interrupts to prevent another IRQ from firing
                        ; which could possibly cause conflicts in our kernel
    push byte 10        ; Note that we DON'T push a value on the stack
                        ; in this one. It pushes one already. Use this type
                        ; of stub for exceptions that pop error codes.
    jmp isr_common_stub ; To track which interrupt is fired

; ISR 11: Segment Not Present Exception (With Error Code)
isr11:
    cli                 ; Clear/disable interrupts to prevent another IRQ from firing
                        ; which could possibly cause conflicts in our kernel
    push byte 11        ; Note that we DON'T push a value on the stack
                        ; in this one. It pushes one already. Use this type
                        ; of stub for exceptions that pop error codes.
    jmp isr_common_stub ; To track which interrupt is fired

; ISR 12: Stack Fault Exception (With Error Code)
isr12:
    cli                 ; Clear/disable interrupts to prevent another IRQ from firing
                        ; which could possibly cause conflicts in our kernel
    push byte 12        ; Note that we DON'T push a value on the stack
                        ; in this one. It pushes one already. Use this type
                        ; of stub for exceptions that pop error codes.
    jmp isr_common_stub ; To track which interrupt is fired

; ISR 13: General Protection Fault Exception (With Error Code)
isr13:
    cli                 ; Clear/disable interrupts to prevent another IRQ from firing
                        ; which could possibly cause conflicts in our kernel
    push byte 13        ; Note that we DON'T push a value on the stack
                        ; in this one. It pushes one already. Use this type
                        ; of stub for exceptions that pop error codes.
    jmp isr_common_stub ; To track which interrupt is fired

; ISR 14: Page Fault Exception (With Error Code)
isr14:
    cli                 ; Clear/disable interrupts to prevent another IRQ from firing
                        ; which could possibly cause conflicts in our kernel
    push byte 14        ; Note that we DON'T push a value on the stack
                        ; in this one. It pushes one already. Use this type
                        ; of stub for exceptions that pop error codes.
    jmp isr_common_stub ; To track which interrupt is fired

; ISR 15: Unknown Interrupt Exception
isr15:
    cli                 ; Clear/disable interrupts to prevent another IRQ from firing
                        ; which could possibly cause conflicts in our kernel
    push byte 0         ; A normal ISR stub that pops a dummy error code 
                        ; to keep a uniform stack frame
    push byte 15        ; To track which interrupt is fired
    jmp isr_common_stub

; ISR 16: Coprocessor Fault Exception
isr16:
    cli                 ; Clear/disable interrupts to prevent another IRQ from firing
                        ; which could possibly cause conflicts in our kernel
    push byte 0         ; A normal ISR stub that pops a dummy error code 
                        ; to keep a uniform stack frame
    push byte 16        ; To track which interrupt is fired
    jmp isr_common_stub

; ISR 17: Alignment Check Exception (486+)
isr17:
    cli                 ; Clear/disable interrupts to prevent another IRQ from firing
                        ; which could possibly cause conflicts in our kernel
    push byte 0         ; A normal ISR stub that pops a dummy error code 
                        ; to keep a uniform stack frame
    push byte 17        ; To track which interrupt is fired
    jmp isr_common_stub

; ISR 18: Machine Check Exception (Pentium/586+)
isr18:
    cli                 ; Clear/disable interrupts to prevent another IRQ from firing
                        ; which could possibly cause conflicts in our kernel
    push byte 0         ; A normal ISR stub that pops a dummy error code 
                        ; to keep a uniform stack frame
    push byte 18        ; To track which interrupt is fired
    jmp isr_common_stub

; REMAINING ISRs (19 to 31) ARE RESERVED EXCEPTIONS (No Error Code)

; ISR 19: Reserved Exception
isr19:
    cli                 ; Clear/disable interrupts to prevent another IRQ from firing
                        ; which could possibly cause conflicts in our kernel
    push byte 0         ; A normal ISR stub that pops a dummy error code 
                        ; to keep a uniform stack frame
    push byte 19        ; To track which interrupt is fired
    jmp isr_common_stub
    
; ISR 20: Reserved Exception
isr20:
    cli                 ; Clear/disable interrupts to prevent another IRQ from firing
                        ; which could possibly cause conflicts in our kernel
    push byte 0         ; A normal ISR stub that pops a dummy error code 
                        ; to keep a uniform stack frame
    push byte 20        ; To track which interrupt is fired
    jmp isr_common_stub
    
; ISR 21: Reserved Exception
isr21:
    cli                 ; Clear/disable interrupts to prevent another IRQ from firing
                        ; which could possibly cause conflicts in our kernel
    push byte 0         ; A normal ISR stub that pops a dummy error code 
                        ; to keep a uniform stack frame
    push byte 21        ; To track which interrupt is fired
    jmp isr_common_stub
    
; ISR 22: Reserved Exception
isr22:
    cli                 ; Clear/disable interrupts to prevent another IRQ from firing
                        ; which could possibly cause conflicts in our kernel
    push byte 0         ; A normal ISR stub that pops a dummy error code 
                        ; to keep a uniform stack frame
    push byte 22        ; To track which interrupt is fired
    jmp isr_common_stub
    
; ISR 23: Reserved Exception
isr23:
    cli                 ; Clear/disable interrupts to prevent another IRQ from firing
                        ; which could possibly cause conflicts in our kernel
    push byte 0         ; A normal ISR stub that pops a dummy error code 
                        ; to keep a uniform stack frame
    push byte 23        ; To track which interrupt is fired
    jmp isr_common_stub
    
; ISR 24: Reserved Exception
isr24:
    cli                 ; Clear/disable interrupts to prevent another IRQ from firing
                        ; which could possibly cause conflicts in our kernel
    push byte 0         ; A normal ISR stub that pops a dummy error code 
                        ; to keep a uniform stack frame
    push byte 24        ; To track which interrupt is fired
    jmp isr_common_stub
    
; ISR 25: Reserved Exception
isr25:
    cli                 ; Clear/disable interrupts to prevent another IRQ from firing
                        ; which could possibly cause conflicts in our kernel
    push byte 0         ; A normal ISR stub that pops a dummy error code 
                        ; to keep a uniform stack frame
    push byte 25        ; To track which interrupt is fired
    jmp isr_common_stub
    
; ISR 26: Reserved Exception
isr26:
    cli                 ; Clear/disable interrupts to prevent another IRQ from firing
                        ; which could possibly cause conflicts in our kernel
    push byte 0         ; A normal ISR stub that pops a dummy error code 
                        ; to keep a uniform stack frame
    push byte 26        ; To track which interrupt is fired
    jmp isr_common_stub
    
; ISR 27: Reserved Exception
isr27:
    cli                 ; Clear/disable interrupts to prevent another IRQ from firing
                        ; which could possibly cause conflicts in our kernel
    push byte 0         ; A normal ISR stub that pops a dummy error code 
                        ; to keep a uniform stack frame
    push byte 27        ; To track which interrupt is fired
    jmp isr_common_stub
    
; ISR 28: Reserved Exception
isr28:
    cli                 ; Clear/disable interrupts to prevent another IRQ from firing
                        ; which could possibly cause conflicts in our kernel
    push byte 0         ; A normal ISR stub that pops a dummy error code 
                        ; to keep a uniform stack frame
    push byte 28        ; To track which interrupt is fired
    jmp isr_common_stub
    
; ISR 29: Reserved Exception
isr29:
    cli                 ; Clear/disable interrupts to prevent another IRQ from firing
                        ; which could possibly cause conflicts in our kernel
    push byte 0         ; A normal ISR stub that pops a dummy error code 
                        ; to keep a uniform stack frame
    push byte 29        ; To track which interrupt is fired
    jmp isr_common_stub
    
; ISR 30: Reserved Exception
isr30:
    cli                 ; Clear/disable interrupts to prevent another IRQ from firing
                        ; which could possibly cause conflicts in our kernel
    push byte 0         ; A normal ISR stub that pops a dummy error code 
                        ; to keep a uniform stack frame
    push byte 30        ; To track which interrupt is fired
    jmp isr_common_stub
    
; ISR 31: Reserved Exception
isr31:
    cli                 ; Clear/disable interrupts to prevent another IRQ from firing
                        ; which could possibly cause conflicts in our kernel
    push byte 0         ; A normal ISR stub that pops a dummy error code 
                        ; to keep a uniform stack frame
    push byte 31        ; To track which interrupt is fired
    jmp isr_common_stub