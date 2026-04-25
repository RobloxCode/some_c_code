#include "../../utils/BitArray/BitArrayImp.h"
#include <stdio.h>
#include <stdlib.h>

int main()
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

    return EXIT_SUCCESS;
}
