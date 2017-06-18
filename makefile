CC=gcc
CFLAGS=-m32 -fno-stack-protector

ASM=nasm -f elf32 
ASMSRC=kernel.asm
# DEPS=keyboard_input.h

SRC=kernel.c keyboard_input.c 
OBJ=kernelc.o keyboard_input.o kasm.o

KERNEL=kernel
LDSCRIPT=-T link.ld
ELF=-m elf_i386
LDFLAGS=$(ELF) $(LDSCRIPT)

default: all

kernelc:
	$(CC) $(CFLAGS) -c kernel.c -o kernelc.o

keyboardinput:
	$(CC) $(CFLAGS) -c keyboard_input.c -o keyboard_input.o

kasm:
	$(ASM) kernel.asm -o kasm.o

link:
	ld $(LDFLAGS) -o $(KERNEL) $(OBJ)

all: kernelc keyboardinput kasm link

clean:
	$(RM) $(OBJ)

clean-all: 
	$(RM) $(OBJ) $(KERNEL)