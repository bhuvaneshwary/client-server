#include <stdio.h>

int main()
{
    int x = 0x12345678;

    unsigned char *p = (unsigned char *)&x;

    printf("Byte 0: %d\n", p[0]);
    printf("Byte 1: %d\n", p[1]);
    printf("Byte 2: %d\n", p[2]);
    printf("Byte 3: %d\n", p[3]);

    return 0;
}