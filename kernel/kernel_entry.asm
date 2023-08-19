global kernel_entry
kernel_entry:
    [bits 32]
    [extern main]
    call main
    jmp $       ; Hang forever when we return from kernel