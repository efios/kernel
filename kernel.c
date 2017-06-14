/* gcc -m32 -c kernel.c -o kernelc.o */

void kernel_main()
{
    const char *string = "My first kernel!";
    char *vidptr = (char*)0xb8000;

    unsigned int i = 0, j = 0, k = 0;

    while(j < 80 * 25 * 2)
    {
        vidptr[j] = ' ';
        vidptr[j + 1] = 0x07;
        j = j + 2;
    }
  
    while(string[k] != '\0')
    {
        vidptr[i] = string[k];

        vidptr[i + 1] = 0x07;
        i = i + 2;
    }
    return;
}