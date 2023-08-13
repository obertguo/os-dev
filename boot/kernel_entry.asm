[bits 32]
[extern main]

kernel_entry:
    mov ebx, MSG_PM_MODE
    call print_string_pm

    call main               ; jump to address where the kernel is
                            ; and hope for the best

    jmp $                   ; Hang
