# Compiler flags
CFLAGS= -ffreestanding -c -nostdlib -m32 -fno-pie -Wall -Wextra -std=c99
NASMFLAGS= -f bin -I ./boot
# LDFLAGS= -m elf_i386 -Ttext-segment 0x1000 -Trodata-segment 0x2000 --oformat binary
LDFLAGS= -m elf_i386 -T script.lds --oformat binary

# Auto generate lists of sources
C_FILES=$(wildcard kernel/*.c kernel/*/*.c kernel/*/*/*.c drivers/*.c shell/*.c)
C_OBJ_FILES=$(C_FILES:.c=.o) # This is needed for the implicit %.o: %.c rule later

ASM_FILES=$(wildcard kernel/*.asm kernel/*/.asm kernel/*/*/*.asm drivers/*.asm)
ASM_OBJ_FILES=$(ASM_FILES:.asm=.o)

SUB_DIRS=$(wildcard kernel/*.)
# TODO: Make sources depend on all header files

echo:
	echo ${C_FILES}

# Default build target
all: os-image

# Run Qemu to simulate and test resulting code
run: os-image
	qemu-system-x86_64 -drive format=raw,file=os-image

clean:
	rm -rf *.bin *.o os-image
	rm -rf ${C_OBJ_FILES}
	rm -rf ${ASM_OBJ_FILES}

# Assemble compiled bootloader binary with compiled kernel binary
os-image: boot.bin kernel.bin
	cat boot.bin kernel.bin > os-image

# Assemble bootloader binary
boot.bin:
	nasm ${NASMFLAGS} boot/boot.asm -o boot.bin

# Assemble C kernel binary 
# Note: $^ is all dependencies, $< is first dependency, $@ is target file
# Note: The linker respects the order of files we are linking
# 		so we want the kernel entry file to always be first
#		as that will call our main C kernel function
kernel.bin: kernel/kernel_entry.o ${ASM_OBJ_FILES} ${C_OBJ_FILES}
	ld ${LDFLAGS} $^ -o kernel.bin

# Generic rule to compile C code into object files
# For simplicity, C files depend on all header files
%.o: %.c
	gcc ${CFLAGS} $< -o $@

# Generic rule to compile ASM code into object files
%.o: %.asm
	nasm -f elf32 $< -o $@

# Compile our simple kernel entry asm file into an object file
kernel/kernel_entry.o: kernel/kernel_entry.asm
	nasm -f elf32 kernel/kernel_entry.asm -o kernel/kernel_entry.o