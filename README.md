# os-dev
A journey in OS development starting from scratch, using assembly (and hopefully later, C for the kernel)

Credit to Nick Blundell for creating a comprehensive writeup for OS development, which this project will initially be following along with, https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf 

# Getting Started
The project uses the NASM compiler to compile assembly files, the GCC compiler to compile C files, and the LD GNU linker to link resulting object files.

The entry point for the bootloader is `boot.asm` and the entry point for the kernel is `kernel.c`. 

To compile the project in Linux, use `make`. The resulting raw os image is found in the project directory named `os-image`. 

To run the program using Qemu, use `make run`. 

To clean the project, removing all intermediate object and raw binary files, as well as the final os image, use `make clean`. 

To run the OS in Qemu, use `qemu-system-x86_64.exe image` or `make run`.
