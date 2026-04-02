#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "../utils/FlexibleArrayMember/FlexibleArrayMemberImp.h"

int test_FlexArr(void) {
    FA_status status = FA_OK;
    size_t len = 5;

    FlexArr *fa = FlexArr_init(len);
    if (!fa)
        return -1;

    if ((status = FlexArr_println(fa)) != FA_OK)
        goto cleanup;

    for (int i = 1; i <= 20; ++i) {
        if ((status = FlexArr_push(&fa, i)) != FA_OK)
            goto cleanup;
    }

    if ((status = FlexArr_println(fa)) != FA_OK)
        goto cleanup;

    if ((status = FlexArr_pop(fa)) != FA_OK)
        goto cleanup;

    if ((status = FlexArr_println(fa)) != FA_OK)
        goto cleanup;

    size_t i = FlexArr_len(fa);
    int num = 0;
    if ((status = FlexArr_get(fa, i, &num)) != FA_OK)
            goto cleanup;

    printf("i: %zu\narr[i]: %d\n", i, num);

cleanup:
    FlexArr_deinit(&fa);
    if (status != FA_OK) {
        fprintf(stderr, "Error status: %d\n", status);
        return -1;
    }

    return 0;
}

int main(void) {
    if (test_FlexArr() < 0)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
