#include "../../utils/FlexibleArrayMember/FlexibleArrayMemberImp.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int test_FlexArr(void) {
    FA_status status = FA_OK;
    size_t len = 5;

    FlexArr *fa = flex_arr_init(len);
    if (!fa) {
        return -1;
    }

    if ((status = flex_arr_println(fa)) != FA_OK) {
        goto cleanup;
    }

    for (int i = 1; i <= 20; ++i) {
        if ((status = flex_arr_push(&fa, i)) != FA_OK) {
            goto cleanup;
        }
    }

    if ((status = flex_arr_println(fa)) != FA_OK) {
        goto cleanup;
    }

    if ((status = flex_arr_pop(fa)) != FA_OK) {
        goto cleanup;
    }

    if ((status = flex_arr_println(fa)) != FA_OK) {
        goto cleanup;
    }

    size_t i = flex_arr_len(fa);
    int num = 0;
    if ((status = flex_arr_get(fa, i, &num)) != FA_OK) {
        goto cleanup;
    }

    printf("i: %zu\narr[i]: %d\n", i, num);

cleanup:
    flex_arr_deinit(&fa);
    if (status != FA_OK) {
        fprintf(stderr, "Error status: %d\n", status);
        return -1;
    }

    return 0;
}

int main(void) {
    if (test_FlexArr() < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
