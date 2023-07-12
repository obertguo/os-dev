CFLAGS= -ffreestanding -c -nostdlib -m32 -fno-pie -Wall -Wextra -Werror -std=c99
NASM=nasm
NASMFLAGS= -f bin
LDFLAGS= -m elf_i386 -Ttext 0x1000 --oformat binary

all: os-image

run: os-image
	qemu-system-x86_64.exe os-image 

clean:
	rm -rf *.bin *.o os-image

os-image: boot.bin kernel.bin
	cat boot.bin kernel.bin > os-image

boot.bin:
	${NASM} ${NASMFLAGS} boot.asm -o boot.bin

kernel.bin: kernel.o
	ld ${LDFLAGS} kernel.o -o kernel.bin

kernel.o: kernel.c
	gcc ${CFLAGS} kernel.c -o kernel.o
