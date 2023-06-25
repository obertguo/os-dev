# os-dev
A journey in OS development starting from scratch, using assembly (and hopefully later, C for the kernel)

Credit to Nick Blundell for creating a comprehensive writeup for OS development, which this project will initially be following along with, https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf 

# Getting Started
The project uses the NASM compiler to compile assembly files. 

The main entry point is `boot.asm`, and can be compiled with `nasm -f bin boot.asm -o boot.bin`. 

The resulting `boot.bin` file contains raw binary data containing the boot sector program, and be executed virtually in Qemu or Bochs.

To run in the program in Qemu (in Windows), execute `qemu-system-x86_64.exe boot.bin`.
