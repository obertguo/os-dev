virtual_base = 0xC0000000;
physical_base = 0x00001000;

OUTPUT_FORMAT("elf32-i386")
ENTRY(kernel_entry)

SECTIONS {
    . = virtual_base;
    .text ALIGN (4096) : AT(ADDR(.text) - virtual_base) {
        *(.text);
        *(.rodata);
        *(.data);
        *(.bss);
        *(COMMON);
    }
}

