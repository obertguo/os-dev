; ISR 32 to 47 are for those raised by master and slave PIC
; https://wiki.osdev.org/8259_PIC
; http://www.osdever.net/bkerndev/Docs/irqs.htm

global isr32
global isr33
global isr34
global isr35
global isr36
global isr37
global isr38
global isr39
global isr40
global isr41
global isr42
global isr43 
global isr44
global isr45
global isr46
global isr47

[extern irq_handler]
irq_common_stub:
    pusha
    push ds
    push es
    push fs 
    push gs

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov eax, esp
    push eax

    call irq_handler

    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    
    add esp, 8
    iret

isr32:
    cli                 ; Clear/disable interrupts to prevent another IRQ from firing
                        ; which could possibly cause conflicts in our kernel
    push byte 0         ; A normal ISR stub that pops a dummy error code 
                        ; to keep a uniform stack frame
    push byte 32        ; To track which interrupt is fired
    jmp irq_common_stub
    
    isr33:
    cli                 ; Clear/disable interrupts to prevent another IRQ from firing
                        ; which could possibly cause conflicts in our kernel
    push byte 0         ; A normal ISR stub that pops a dummy error code 
                        ; to keep a uniform stack frame
    push byte 33        ; To track which interrupt is fired
    jmp irq_common_stub
    
    isr34:
    cli                 ; Clear/disable interrupts to prevent another IRQ from firing
                        ; which could possibly cause conflicts in our kernel
    push byte 0         ; A normal ISR stub that pops a dummy error code 
                        ; to keep a uniform stack frame
    push byte 34        ; To track which interrupt is fired
    jmp irq_common_stub
    
    isr35:
    cli                 ; Clear/disable interrupts to prevent another IRQ from firing
                        ; which could possibly cause conflicts in our kernel
    push byte 0         ; A normal ISR stub that pops a dummy error code 
                        ; to keep a uniform stack frame
    push byte 35        ; To track which interrupt is fired
    jmp irq_common_stub
    
    isr36:
    cli                 ; Clear/disable interrupts to prevent another IRQ from firing
                        ; which could possibly cause conflicts in our kernel
    push byte 0         ; A normal ISR stub that pops a dummy error code 
                        ; to keep a uniform stack frame
    push byte 36        ; To track which interrupt is fired
    jmp irq_common_stub
    
    isr37:
    cli                 ; Clear/disable interrupts to prevent another IRQ from firing
                        ; which could possibly cause conflicts in our kernel
    push byte 0         ; A normal ISR stub that pops a dummy error code 
                        ; to keep a uniform stack frame
    push byte 37        ; To track which interrupt is fired
    jmp irq_common_stub
    
    isr38:
    cli                 ; Clear/disable interrupts to prevent another IRQ from firing
                        ; which could possibly cause conflicts in our kernel
    push byte 0         ; A normal ISR stub that pops a dummy error code 
                        ; to keep a uniform stack frame
    push byte 38        ; To track which interrupt is fired
    jmp irq_common_stub
    
    isr39:
    cli                 ; Clear/disable interrupts to prevent another IRQ from firing
                        ; which could possibly cause conflicts in our kernel
    push byte 0         ; A normal ISR stub that pops a dummy error code 
                        ; to keep a uniform stack frame
    push byte 39        ; To track which interrupt is fired
    jmp irq_common_stub
    
    isr40:
    cli                 ; Clear/disable interrupts to prevent another IRQ from firing
                        ; which could possibly cause conflicts in our kernel
    push byte 0         ; A normal ISR stub that pops a dummy error code 
                        ; to keep a uniform stack frame
    push byte 40        ; To track which interrupt is fired
    jmp irq_common_stub
    
    isr41:
    cli                 ; Clear/disable interrupts to prevent another IRQ from firing
                        ; which could possibly cause conflicts in our kernel
    push byte 0         ; A normal ISR stub that pops a dummy error code 
                        ; to keep a uniform stack frame
    push byte 41        ; To track which interrupt is fired
    jmp irq_common_stub
    
    isr42:
    cli                 ; Clear/disable interrupts to prevent another IRQ from firing
                        ; which could possibly cause conflicts in our kernel
    push byte 0         ; A normal ISR stub that pops a dummy error code 
                        ; to keep a uniform stack frame
    push byte 42        ; To track which interrupt is fired
    jmp irq_common_stub
    
    isr43:
    cli                 ; Clear/disable interrupts to prevent another IRQ from firing
                        ; which could possibly cause conflicts in our kernel
    push byte 0         ; A normal ISR stub that pops a dummy error code 
                        ; to keep a uniform stack frame
    push byte 43        ; To track which interrupt is fired
    jmp irq_common_stub
    
    isr44:
    cli                 ; Clear/disable interrupts to prevent another IRQ from firing
                        ; which could possibly cause conflicts in our kernel
    push byte 0         ; A normal ISR stub that pops a dummy error code 
                        ; to keep a uniform stack frame
    push byte 44        ; To track which interrupt is fired
    jmp irq_common_stub
    
    isr45:
    cli                 ; Clear/disable interrupts to prevent another IRQ from firing
                        ; which could possibly cause conflicts in our kernel
    push byte 0         ; A normal ISR stub that pops a dummy error code 
                        ; to keep a uniform stack frame
    push byte 45        ; To track which interrupt is fired
    jmp irq_common_stub
    
    isr46:
    cli                 ; Clear/disable interrupts to prevent another IRQ from firing
                        ; which could possibly cause conflicts in our kernel
    push byte 0         ; A normal ISR stub that pops a dummy error code 
                        ; to keep a uniform stack frame
    push byte 46        ; To track which interrupt is fired
    jmp irq_common_stub
    
    isr47:
    cli                 ; Clear/disable interrupts to prevent another IRQ from firing
                        ; which could possibly cause conflicts in our kernel
    push byte 0         ; A normal ISR stub that pops a dummy error code 
                        ; to keep a uniform stack frame
    push byte 47        ; To track which interrupt is fired
    jmp irq_common_stub