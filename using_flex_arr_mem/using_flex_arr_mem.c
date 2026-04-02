#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "../utils/FlexibleArrayMember/FlexibleArrayMemberImp.h"

int test_FlexArr(void) {
    size_t len = 5;
    FlexArr *fa = FlexArr_init(len);
    if (!fa)
        return -1;

    FlexArr_println(fa);

    for (int i = 1; i <= 20; ++i) {
        if (FlexArr_push(&fa, i) < 0)
            return -1;
    }

    FlexArr_println(fa);
    FlexArr_deinit(&fa);
    return 0;
}

int main(void) {
    if (test_FlexArr() < 0)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
