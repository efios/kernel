/* kernel .c */
/* gcc -m32 -c kernel.c -o kernelc.o */

#define VIDEO_START 0xb8000		       
#define MAX_LINES 25
#define CHARACTERS_PER_LINE 80
#define BYTES_PER_ELEMENT 2

#define LIGHT_GRAY 0x07

#define IDT_SIZE 256
#define KERNEL_SEGMENT_OFFSET 0x08
#define INTERRUPT_GATE 0x8e

#define PIC1_COMMAND 0x20
#define PIC1_DATA 0x21

#define PIC2_COMMAND 0xA0
#define PIC2_DATA 0xA1

struct IDT_entry{
  unsigned short int offset_lowerbits;
  unsigned short int selector;
  unsigned char zero;
  unsigned char type_attribute;
  unsigned short int offset_higherbits;
};

struct IDT_entry IDT[IDT_SIZE];

void idt_init(void)
{
  unsigned long keyboard_address;
  unsigned long idt_address;
  unsigned long idt_ptr[2];

  keyboard_address = (unsigned long)keyboard_handler;
  IDT[0x21].offset_lowerbits = keyboard_address & 0xffff;
  IDT[0x21].selector = KERNEL_SEGMENT_OFFSET;
  IDT[0x21].zero = 0;
  IDT[0x21].type_attribute = INTERRUPT_GATE;
  IDT[0x21].offset_higherbits = (keyboard_address & 0xffff0000) >> 16;

  /* ICW1 - begin initialization */
  write_port(PIC1_COMMAND, 0x11);
  write_port(PIC2_COMMAND, 0x11);

  /* ICW2 - remap offset address of IDT */
  write_port(PIC1_DATA, 0x20);
  write_port(PIC2_DATA, 0x28);

  /* ICW3 - setup cascading */
  write_port(PIC1_DATA, 0x00);
  write_port(PIC2_DATA, 0x00);

  /* ICW4 - environment info */
  write_port(PIC1_DATA, 0x01);
  write_port(PIC2_DATA, 0x01);

  /* Mask interrupts */
  write_port(PIC1_DATA, 0xff);
  write_port(PIC2_DATA, 0xff);

  idt_address = (unsigned long)IDT;
  idt_ptr[0] = (sizeof(struct IDT_entry) * IDT_SIZE) +
    ((idt_address & 0xffff) << 16);

  idt_ptr[1] = idt_address >> 16;
  load_idt(idt_ptr);
}

void kernel_clear_screen() { }

void kernel_main()
{
    const char *string = "My first kernel!";
    char *vidptr = (char*)VIDEO_START;

    unsigned int i = 0, j = 0, k = 0;

    while(j < CHARACTERS_PER_LINE * MAX_LINES * BYTES_PER_ELEMENT)
    {
        vidptr[j] = ' ';
        vidptr[j + 1] = LIGHT_GRAY;
        j = j + 2;
    }
  
    while(string[k] != '\0')
    {
        vidptr[i] = string[k];

        vidptr[i + 1] = LIGHT_GRAY;
        i = i + 2;
	++k;
    }
    return;
}
