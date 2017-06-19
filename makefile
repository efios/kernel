CC=gcc
CFLAGS=-m32 -fno-stack-protector

ASM=nasm -f elf32 

RMDIR_R=rmdir
MKDIR_P=mkdir -p

SDIR=source/
# "Input directory"
IDIR=$(SDIR)kinput/

BDIR=bin/
# "Temp directory"
TDIR=$(BDIR)temp/

ASMSRC=$(SDIR)kernel.asm
SRC=$(SDIR)kernel.c $(SDIR)keyboard_input.c 
OBJ=kernelc.o keyboard_input.o kasm.o

KERNEL=kernel
LDSCRIPT=-T link.ld
ELF=-m elf_i386
LDFLAGS=$(ELF) $(LDSCRIPT)

default: all

bin:
	$(MKDIR_P) $(BDIR)

temp:
	$(MKDIR_P) $(TDIR)

kernelc:
	$(CC) $(CFLAGS) -c $(SDIR)kernel.c -o $(TDIR)kernelc.o

keyboardinput:
	$(CC) $(CFLAGS) -c $(IDIR)keyboard_input.c -o $(TDIR)keyboard_input.o

kasm:
	$(ASM) $(ASMSRC) -o $(TDIR)kasm.o

link:
	ld $(LDFLAGS) -o $(BDIR)$(KERNEL) $(TDIR)*.o

all: bin temp  kernelc keyboardinput kasm link

clean:
	$(RM) $(TDIR)*.o

RM-bin:
	$(RMDIR_R) $(BDIR)

RM-temp:
	$(RMDIR_R) $(TDIR)
	
clean-temp:
	$(RM) $(TDIR)*.o

clean-bin:
	$(RM) $(BDIR)$(KERNEL)

clean-all: clean-temp clean-bin RM-temp RM-bin 
