#include "ArrayListImp.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <limits.h>

ArrayList *ArrayList_init(const size_t cap) {
    if (cap == 0)
        return NULL;

    int *items = calloc(cap, sizeof *items);
    if (!items)
        return NULL;

    ArrayList *al = malloc(sizeof *al);
    if (!al) {
        free(items);
        return NULL;
    }

    al->items = items;
    al->capacity = cap;
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

    for (int i = (int)al->length - 1; i >= 0; --i)
        buff[(int)al->length - i - 1] = al->items[i];

    for (size_t i = 0; i < al->length; ++i)
        al->items[i] = buff[i];

    return ARRAYLIST_OK;
}

ArrayList_status ArrayList_copy(const ArrayList *src, ArrayList *dst) {
    if (!src || !dst)
        return ARRAYLIST_ERR_WRONG_PTR;

    if (src->capacity > dst->capacity)
        return ARRAYLIST_ERR_SRC_LARGER_THAN_DST;

    ArrayList_status status = ARRAYLIST_OK;
    for (size_t i = 0; i < src->length; ++i) {
        if ((status = ArrayList_append(dst, src->items[i])) != ARRAYLIST_OK)
            return status;
    }

    return ARRAYLIST_OK;
}

size_t ArrayList_len(const ArrayList *al) {
    if (!al)
        return 0;

    return al->length;
}

ArrayList_status ArrayList_swap(
    ArrayList *al,
    const size_t i1,
    const size_t i2
) {
    if (!al)
        return ARRAYLIST_ERR_WRONG_PTR;

    if (i1 >= al->length || i2 >= al->length)
        return ARRAYLIST_IDX_OUT_OF_RANGE;

    int tmp = al->items[i1];
    al->items[i1] = al->items[i2];
    al->items[i2] = tmp;

    return ARRAYLIST_OK;
}

int ArrayList_get(ArrayList *al, const size_t i) {
    if (!al)
        return INT_MAX;

    if (i >= al->length)
        return INT_MAX;

    return al->items[i];
}

ArrayList_status ArrayList_remove(ArrayList *al, const size_t i) {
    if (!al)
        return ARRAYLIST_ERR_WRONG_PTR;

    if (i >= al->length)
        return ARRAYLIST_IDX_OUT_OF_RANGE;

    for (size_t j = i; j < al->length - 1; ++j)
        ArrayList_swap(al, j, j + 1);

    al->length--;

    return ARRAYLIST_OK;
}

// this function has a problem (dont know what it is yet)
ArrayList *_helper(ArrayList *left, ArrayList *right) {
    ArrayList *sorted = ArrayList_init(left->length + right->length);
    if (!sorted)
        return NULL;

    size_t i = 0;
    size_t j = 0;

    while (i < left->length && j < right->length) {
        if (left->items[i] < right->items[j])
            ArrayList_append(sorted, left->items[i++]);
        else
            ArrayList_append(sorted, right->items[j++]);
    }

    while (i < left->length)
        ArrayList_append(sorted, left->items[i++]);

    while (j < right->length)
        ArrayList_append(sorted, right->items[j++]);

    return sorted;
}

ArrayList *sort(ArrayList *al) {
    if (!al || al->length <= 1)
        return al;

    size_t mid = al->length / 2;

    ArrayList *left = ArrayList_init(mid);
    ArrayList *right = ArrayList_init(al->length - mid);

    if (!left || !right) {
        ArrayList_deinit(&left);
        ArrayList_deinit(&right);
        return NULL;
    }

    for (size_t i = 0; i < mid; ++i)
        ArrayList_append(left, al->items[i]);

    for (size_t i = mid; i < al->length; ++i)
        ArrayList_append(right, al->items[i]);

    left = sort(left);
    right = sort(right);

    ArrayList *result = _helper(left, right);

    ArrayList_deinit(&left);
    ArrayList_deinit(&right);

    return result;
}
