OUTPUT_FORMAT("elf32-i386")
ENTRY(kernel_entry)
SECTIONS {
    . = 0x1000;
    .text : {
        *(.text);
        *(.text.*);
        *(.rodata);
    }
}