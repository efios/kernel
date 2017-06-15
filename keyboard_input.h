#ifndef KEYBOARD_INPUT_H
#define KEYBOARD_INPUT_H

#define IDT_SIZE 256
#define KERNEL_SEGMENT_OFFSET 0x08
#define INTERRUPT_GATE 0x8e

#define PIC1_COMMAND 0x20
#define PIC1_DATA 0x21

#define PIC2_COMMAND 0xA0
#define PIC2_DATA 0xA1

#define INITIALIZE_COMMAND 0x11

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64


extern char *vidptr;
extern unsigned int current_location;
extern unsigned char keyboard_map[128];
extern void keyboard_handler(void);
extern char read_port(unsigned short port);
extern char write_port(unsigned short port, unsigned char data);
extern void load_idt(unsigned long *idt_ptr);


struct IDT_entry{
  unsigned short int offset_lowerbits;
  unsigned short int selector;
  unsigned char zero;
  unsigned char type_attribute;
  unsigned short int offset_higherbits;
};


struct IDT_entry IDT[IDT_SIZE];

void init_idt(void);

void keyboard_init(void);

void keyboard_handler_main(void);

#endif