nasm boot.asm -f bin -o boot.bin

nasm ExtendedProgram.asm -f elf64 -o ExtendedProgram.o

x86_64-elf-gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "Kernel.cpp" -o "Kernel.o"

x86_64-elf-ld -T"link.ld"

cat boot.bin kernel.bin > boot.flp
