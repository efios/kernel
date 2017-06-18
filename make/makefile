CC=gcc
CFLAGS=-m32 -fno-stack-protector

ASM=nasm -f elf32 

SDIR= ../source/
# "Input directory"
IDIR= $(SDIR)kinput/

BDIR= ../bin/
# "Temp directory"
TDIR= $(BDIR)temp/

ASMSRC=$(SDIR)kernel.asm
SRC=$(SDIR)kernel.c $(SDIR)keyboard_input.c 
OBJ=kernelc.o keyboard_input.o kasm.o

KERNEL=kernel
LDSCRIPT=-T link.ld
ELF=-m elf_i386
LDFLAGS=$(ELF) $(LDSCRIPT)

default: all

kernelc:
	$(CC) $(CFLAGS) -c $(SDIR)kernel.c -o $(TDIR)kernelc.o

keyboardinput:
	$(CC) $(CFLAGS) -c $(IDIR)keyboard_input.c -o $(TDIR)keyboard_input.o

kasm:
	$(ASM) $(ASMSRC) -o $(TDIR)kasm.o

link:
	ld $(LDFLAGS) -o $(BDIR)$(KERNEL) $(TDIR)*.o

all: kernelc keyboardinput kasm link

clean:
	$(RM) $(TDIR)*.o

clean-all: 
	$(RM) $(TDIR)*.o $(BDIR)$(KERNEL)
