#include "../../utils/BitArray/BitArrayImp.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>

// int main(void)
// {
//     uint32_t x = 42;
//     printf("x: %d\n", x);
//     print_bin(x);
//
//     for (int i = 0; i < 8; ++i)
//         printf("i: %d bit: %d\n", i, (x >> i) & 0x1);
//
//     return EXIT_SUCCESS;
// }

int main(void)
{
    struct u8_BitArr bitArr = {0};
    if (u8_BitArr_print(&bitArr) != 0)
        return EXIT_FAILURE;

    if (u8_BitArr_set(&bitArr, 0) != 0)
        return EXIT_FAILURE;

    if (u8_BitArr_set(&bitArr, 1) != 0)
        return EXIT_FAILURE;

    if (u8_BitArr_set(&bitArr, 7) != 0)
        return EXIT_FAILURE;

    if (u8_BitArr_print(&bitArr) != 0)
        return EXIT_FAILURE;

    if (u8_BitArr_clear(&bitArr, 0) != 0)
        return EXIT_FAILURE;

    if (u8_BitArr_print(&bitArr) != 0)
        return EXIT_FAILURE;

    int bit = 0;
    for (int i = 0; i < 8; ++i) {
        if (u8_BitArr_get(&bitArr, i, &bit) != 0)
            return EXIT_FAILURE;

        printf("bit %d: %d\n", i, bit);
    }

    return EXIT_SUCCESS;
}
