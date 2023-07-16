print_hex:
    ; bx stores address of string
    ; dx is used internally to compute printable hex char and print
    
    print_hex_setup:
        pusha

    print_hex_begin:
        cmp byte [bx], 0x0
        je print_hex_done
        
        process_high_nibble:
            mov dx, [bx]
            shr dl, 4
            cmp dl, 10
            jl high_to_num

            high_to_alph:
                add dl, 'a'
                sub dl, 10
                jmp print_high_nibble
            high_to_num:
                add dl, '0'
            
            print_high_nibble:
                call print_char

        process_low_nibble:
            mov dx, [bx]
            and dl, 0x0f
            cmp dl, 10
            jl low_to_num

            low_to_alph:
                add dl, 'a'
                sub dl, 10
                jmp print_low_nibble
            low_to_num:
                add dl, '0'

            print_low_nibble:
                call print_char

            ; output formatting with space after every printed byte
            mov dl, ' '
            call print_char
                
        print_hex_next_char:
            add bx, 1
            jmp print_hex_begin

    print_hex_done:
        popa
        ret