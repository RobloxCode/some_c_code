#include "FlexibleArrayMemberImp.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

FlexArr *FlexArr_init(const size_t cap) {
    if (cap == 0)
        return NULL;

    FlexArr *fa = calloc(1, sizeof *fa + cap * sizeof(int));
    if (!fa)
        return NULL;

    fa->cap = cap;

    return fa;
}

FA_status FlexArr_deinit(FlexArr **fa) {
    if (!fa || !*fa)
        return FA_ERR_WRONG_PTR;

    free(*fa);
    *fa = NULL;
    return FA_OK;
}

FA_status FlexArr_push(FlexArr **fa, int val) {
    if (!fa || !*fa)
        return FA_ERR_WRONG_PTR;

    if ((*fa)->len >= (*fa)->cap) {
        size_t new_cap = (*fa)->cap * 2;

        FlexArr *tmp = realloc(*fa,
                sizeof **fa + new_cap * sizeof(int));
        if (!tmp)
            return FA_ERR_REALLOC;

        tmp->cap = new_cap;
        *fa = tmp;
    }

    (*fa)->arr[(*fa)->len++] = val;
    return FA_OK;
}

FA_status FlexArr_pop(FlexArr *fa) {
    if (!fa)
        return FA_ERR_WRONG_PTR;

    fa->len--;
    return FA_OK;
}

FA_status FlexArr_get(
    const FlexArr *fa,
    const size_t i,
    int *out
) {
    if (!fa || !out)
        return FA_ERR_WRONG_PTR;

    if (i >= fa->len)
        return FA_ERR_RANGE;

    *out = fa->arr[i];

    return FA_OK;
}

size_t FlexArr_len(const FlexArr *fa) {
    if (!fa)
        return 0;

    return fa->len - 1;
}

FA_status FlexArr_println(const FlexArr *fa) {
    if (!fa)
        return FA_ERR_WRONG_PTR;

    for (size_t i = 0; i < fa->len; ++i)
        printf("%d ", fa->arr[i]);
    printf("\n");
    return FA_OK;
}
