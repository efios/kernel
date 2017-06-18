CC=gcc
CFLAGS=-m32 -fno-stack-protector

ASM=nasm -f elf32 

# DEPS=keyboard_input.h

SRC=kernel.c keyboard_input.c
OBJ=kernelc.o keyboard_input.o kasm.o

EXE=kernel
LINKSCRIPT=link.ld
ELF=elf_i386
LDFLAGS=-m $(ELF) -T $(LINKSCRIPT)

default: all

kernelc:
	$(CC) $(CFLAGS) -c kernel.c -o kernelc.o

keyboardinput:
	$(CC) $(CFLAGS) -c keyboard_input.c -o keyboard_input.o

kasm:
	$(ASM) kernel.asm -o kasm.o

link:
	ld $(LDFLAGS) -o $(EXE) $(OBJ)

all: kernelc keyboardinput kasm link

clean: 
	$(RM) $(OBJ) $(EXE)