/* ld -m elf_i386 -T link.ld -o kernel kasm.o kernelc.o */

OUTPUT_FORMAT(elf32-i386)
ENTRY(start)
SECTIONS
{
    . = 0x100000;
    .text : {*(text)}
    .data : {*(data)}
    .bss  : {*(bss)}
}
