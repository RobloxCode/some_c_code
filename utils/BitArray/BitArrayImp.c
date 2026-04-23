#include "BitArrayImp.h"
#include <stdio.h>

void print_bin(unsigned char num)
{
    for (int i = 7; i >= 0; --i) {
        printf("%d", (num >> i) & 1);
    }
    printf("\n");
}

void set(int *out, int n)
{
    int mask = 0x1;
    mask = mask << n;
    *out = *out | mask;
}

void clear(int *out, int n)
{
    int mask = 0x1;
    mask = ~(mask << n);
    *out = *out & mask;
}
