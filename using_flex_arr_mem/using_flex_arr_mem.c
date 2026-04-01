#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t cap;
    size_t len;
    int arr[];
} FlexArr;

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
