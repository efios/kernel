    ;; kernel.asm
    ; nasm -f elf32 kernel.asm -o kasm.o
    
    ; nasm directive - 32 bit
bits 32
section .text
    ; multiboot spec
    align 4
    dd 0x1BADB002
    dd 0x00
    dd - (0x1BADB002 + 0x00)

global start
extern kernel_main

start:
    cli 
    mov esp, stack_space
    call kernel_main
    hlt

section .bss
resb 8192
stack_space: