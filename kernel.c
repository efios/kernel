/* kernel .c */
/* gcc -m32 -c kernel.c -o kernelc.o */

#define VIDEO_START 0xb8000		       
#define MAX_LINES 25
#define CHARACTERS_PER_LINE 80
#define BYTES_PER_ELEMENT 2

#define LIGHT_GRAY 0x07

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
    }
    return;
}
