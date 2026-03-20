#include "ArrayListImp.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <limits.h>

ArrayList *ArrayList_init(const size_t init_len) {
    if (init_len == 0)
        return NULL;

    int *items = calloc(init_len, sizeof *items);
    if (!items)
        return NULL;

    ArrayList *al = malloc(sizeof *al);
    if (!al) {
        free(items);
        return NULL;
    }

    al->items = items;
    al->capacity = init_len;
    al->length = 0;

    return al;
}

ArrayList_status ArrayList_append(ArrayList *al, const int item) {
    if (!al)
        return ARRAYLIST_ERR_WRONG_PTR;

    if (al->length == al->capacity) {
        if (al->capacity > SIZE_MAX / 2)
            return ARRAYLIST_ERR_OVERFLOW;

        size_t new_len = al->capacity * 2;

        if (new_len > SIZE_MAX / sizeof *al->items)
            return ARRAYLIST_ERR_OVERFLOW;

        int *tmp = realloc(al->items, new_len * sizeof *al->items);
        if (!tmp)
            return ARRAYLIST_ERR_REALLOC;

        al->items = tmp;
        al->capacity = new_len;
    }

    al->items[al->length] = item;
    al->length++;

    return ARRAYLIST_OK;
}

ArrayList_status ArrayList_deinit(ArrayList **al) {
    if (!al || !*al)
        return ARRAYLIST_ERR_WRONG_PTR;

    free((*al)->items);
    free(*al);
    *al = NULL;
    return ARRAYLIST_OK;
}

ArrayList_status ArrayList_println(const ArrayList *al) {
    if (!al)
        return ARRAYLIST_ERR_WRONG_PTR;

    for (size_t i = 0; i < al->length; ++i)
        printf("%d ", al->items[i]);

    printf("\n");

    return ARRAYLIST_OK;
}

ArrayList_status ArrayList_reverse(ArrayList *al) {
    if (!al)
        return ARRAYLIST_ERR_WRONG_PTR;

    int buff[al->length];

    for (int i = (int)al->length; i >= 0; --i)
        buff[(int)al->length - i - 1] = al->items[i];

    for (size_t i = 0; i < al->length; ++i)
        al->items[i] = buff[i];

    return ARRAYLIST_OK;
}
