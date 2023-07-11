CFLAGS= -ffreestanding -c -nostdlib -m32 -Wall -Wextra -Werror -std=c99
NASM=nasm
NASMFLAGS= -f bin
LDFLAGS= -m elf_i386 -Ttext 0x1000 --oformat binary

image: boot.bin kernel.bin
    cat boot.bin kernel.bin > image
boot.bin:
    ${NASM} ${NASMFLAGS} boot.asm -o boot.bin

kernel.bin: kernel.o
    ld ${LDFLAGS} kernel.o -o kernel.bin

kernel.o: kernel.c
    gcc ${CFLAGS} kernel.c -o kernel.o


