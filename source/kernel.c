/* kernel .c */
/* gcc -fno-stack-protector -m32 -c kernel.c keyboard_input.c -o kernelc.o */

#include "kinput/keyboard_input.h"

extern void idt_init(void);
extern void keyboard_init(void);

#define VIDEO_START 0xb8000		       
#define MAX_LINES 25
#define CHARACTERS_PER_LINE 80
#define BYTES_PER_ELEMENT 2
#define LINE_SIZE BYTES_PER_ELEMENT * CHARACTERS_PER_LINE
#define SCREENSIZE BYTES_PER_ELEMENT * CHARACTERS_PER_LINE * MAX_LINES

#define LIGHT_GRAY 0x07

char *vidptr = (char*)VIDEO_START;
unsigned int current_location = 0;

void kernel_clear_screen()
{
  unsigned int i = 0;
  while(i < SCREENSIZE)
    {
      vidptr[i++] = ' ';
      vidptr[i++] = LIGHT_GRAY;
    }
}

void kernel_newline()
{
  current_location = current_location +
    (LINE_SIZE - current_location % (LINE_SIZE));
}

void kernel_print(const char *string)
{
  unsigned int i;
  for(i = 0; string[i] != '\0';)
    vidptr[current_location++] = string[i++];

  /*
  while(string[i] != '\0')
    {
      vidptr[current_location++] = string[i++];
      vidptr[current_location++] = string[i++];
    }
  */
}

void kernel_main(void)
{
    const char *string = "My first kernel!";
    kernel_clear_screen();
    kernel_print(string);
    kernel_print_newline();
    
    idt_init();
    keyboard_init();

    while(1);
}
