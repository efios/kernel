#include "keyboard_map.h"
#include "keyboard_input.h"

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
  write_port(PIC1_COMMAND, INITIALIZE_COMMAND);
  write_port(PIC2_COMMAND, INITIALIZE_COMMAND);

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

void keyboard_init(void)
{
  /* Only enable IRQ1 */
  write_port(PIC1_DATA, 0xFD);
}

void keyboard_handler_main(void)
{
  unsigned char status;
  char keycode;

  /* EOI */
  write_port(PIC1_COMMAND, 0x20);

  status = read_port(KEYBOARD_STATUS_PORT);
  if(status & 0x01)
    {
      keycode = read_port(KEYBOARD_DATA_PORT);
      if(keycode < 0)
	return;
      vidptr[current_location++] = keyboard_map[(unsigned char)keycode];
      vidptr[current_location++] = 0x07;

    }
}

