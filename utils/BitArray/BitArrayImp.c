#include "BitArrayImp.h"
#include <stdio.h>

void print_bin(unsigned char num)
{
    for (int i = 7; i >= 0; --i) {
        printf("%d", (num >> i) & 1);
    }
    printf("\n");
}

int u8_BitArr_print(struct u8_BitArr *ba)
{
    if (!ba)
        return 1;

    for (int i = 7; i >= 0; --i) {
        printf("%d", (ba->items >> i) & 1);
    }
    printf("\n");

    return 0;
}

int u8_BitArr_set(struct u8_BitArr *ba, int n)
{
    if (n > 7 || !ba)
        return 1;

    int mask = 0x1;
    mask = mask << n;
    ba->items = ba->items | mask;

    return 0;
}

int u8_BitArr_clear(struct u8_BitArr *ba, int n)
{
    if (n > 7 || !ba)
        return 1;

    unsigned int mask = 0x1;
    mask = ~(mask << n);
    ba->items = ba->items & mask;

    return 0;
}
