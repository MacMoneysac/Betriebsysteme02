echo Starte Assembler
nasm -f elf32 -o start.o start.asm
echo Starte GCC
gcc -m32 -march=i386 -Wall -O -ffreestanding -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o main.o main.c
gcc -m32 -march=i386 -Wall -O -ffreestanding -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o screen.o screen.c
gcc -m32 -march=i386 -Wall -O -ffreestanding -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o gdt.o gdt.c
gcc -m32 -march=i386 -Wall -O -ffreestanding -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o idt.o idt.c
gcc -m32 -march=i386 -Wall -O -ffreestanding -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o isrs.o isrs.c
gcc -m32 -march=i386 -Wall -O -ffreestanding -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o irq.o irq.c
gcc -m32 -march=i386 -Wall -O -ffreestanding -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o timer.o timer.c
gcc -m32 -march=i386 -Wall -O -ffreestanding -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -I./include -c -o keyboard.o keyboard.c
echo Starte Linker
ld -m elf_i386 -T link.ld --oformat binary -o kernel.bin start.o main.o screen.o gdt.o idt.o isrs.o irq.o timer.o keyboard.o
echo Done!
