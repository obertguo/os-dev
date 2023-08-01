# os-dev
A journey in OS development starting from scratch, using a mix of assembly and C. 

Credit to Nick Blundell for creating a comprehensive paper for the initial necessary guidance for OS development, 
https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf 

# Getting Started
The project uses the NASM compiler to compile assembly files, the GCC compiler to compile C files, and the LD GNU linker to link resulting object files.

The entry point for the bootloader is `boot.asm` and the entry point for the kernel is `kernel.c`. 

To compile the project in Linux, use `make`. The resulting raw os image is found in the project directory named `os-image`. 

To clean the project, removing all intermediate object and raw binary files, as well as the final os image, use `make clean`. 

To run the OS in Qemu, use `qemu-system-x86_64.exe os-image` or `make run`.
