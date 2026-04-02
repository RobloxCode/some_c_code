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

void FlexArr_deinit(FlexArr **fa) {
    if (!fa || !*fa)
        return;

    free(*fa);
    *fa = NULL;
}

int FlexArr_push(FlexArr **fa, int val) {
    if (!fa || !*fa)
        return -1;

    if ((*fa)->len >= (*fa)->cap) {
        size_t new_cap = (*fa)->cap * 2;

        FlexArr *tmp = realloc(*fa,
                sizeof **fa + new_cap * sizeof(int));
        if (!tmp)
            return -2;

        tmp->cap = new_cap;
        *fa = tmp;
    }

    (*fa)->arr[(*fa)->len++] = val;
    return 0;
}

void FlexArr_pop(FlexArr *fa);
int FlexArr_get(FlexArr *fa);

void FlexArr_println(const FlexArr *fa) {
    if (!fa)
        return;

    for (size_t i = 0; i < fa->len; ++i)
        printf("%d ", fa->arr[i]);
    printf("\n");
}
