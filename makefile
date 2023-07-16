# Compiler flags
CFLAGS= -ffreestanding -c -nostdlib -m32 -fno-pie -Wall -Wextra -Werror -std=c99
NASMFLAGS= -f bin -I ./boot
LDFLAGS= -m elf_i386 -Ttext 0x1000 --oformat binary

# Auto generate lists of sources
C_FILES=$(wildcard kernel/*.c drivers/*.c )
C_HEADERS=$(wildcard kernel/*.h drivers/*.h)
OBJ_FILES=${C_FILES:.c=.o}

# TODO: Make sources depend on all header files

# Default build target
all: os-image

# Run Qemu to simulate and test resulting code
run: os-image
	qemu-system-x86_64 os-image 

clean:
	rm -rf *.bin *.o os-image
	rm -rf ${OBJ_FILES}

os-image: boot.bin kernel.bin
	cat boot.bin kernel.bin > os-image

# Assemble boot program binary
boot.bin:
	nasm ${NASMFLAGS} boot/boot.asm -o boot.bin

# Assemble C kernel binary
kernel.bin: ${OBJ_FILES}
	ld ${LDFLAGS} ${OBJ_FILES} -o kernel.bin

# Generic rule to compile C code into object files
# For simplicity, C files depend on all header files
%.o: %.c ${C_HEADERS}
	gcc ${CFLAGS} $< -o $@
