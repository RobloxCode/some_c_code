#include "ArrayListImp.h"

#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

ArrList *array_list_init(const size_t cap) {
    if (cap == 0) {
        return NULL;
    }

    int *items = calloc(cap, sizeof *items);
    if (!items) {
        return NULL;
    }

    ArrList *al = malloc(sizeof *al);
    if (!al) {
        free(items);
        return NULL;
    }

    al->items = items;
    al->capacity = cap;
    al->length = 0;

    return al;
}

AL_status array_list_append(ArrList *al, const int item) {
    if (!al) {
        return ARRAYLIST_ERR_WRONG_PTR;
    }

    if (al->length == al->capacity) {
        if (al->capacity > SIZE_MAX / 2) {
            return ARRAYLIST_ERR_OVERFLOW;
        }

        size_t new_len = al->capacity * 2;

        if (new_len > SIZE_MAX / sizeof *al->items) {
            return ARRAYLIST_ERR_OVERFLOW;
        }

        int *tmp = realloc(al->items, new_len * sizeof *al->items);
        if (!tmp) {
            return ARRAYLIST_ERR_REALLOC;
        }

        al->items = tmp;
        al->capacity = new_len;
    }

    al->items[al->length] = item;
    al->length++;

    return ARRAYLIST_OK;
}

AL_status array_list_deinit(ArrList **al) {
    if (!al || !*al) {
        return ARRAYLIST_ERR_WRONG_PTR;
    }

    free((*al)->items);
    free(*al);
    *al = NULL;

    return ARRAYLIST_OK;
}

AL_status array_list_println(const ArrList *al) {
    if (!al) {
        return ARRAYLIST_ERR_WRONG_PTR;
    }

    for (size_t i = 0; i < al->length; ++i) {
        printf("%d ", al->items[i]);
    }

    printf("\n");

    return ARRAYLIST_OK;
}

AL_status array_list_reverse(ArrList *al) {
    if (!al) {
        return ARRAYLIST_ERR_WRONG_PTR;
    }

    int buff[al->length];

    for (int i = (int)al->length - 1; i >= 0; --i) {
        buff[(int)al->length - i - 1] = al->items[i];
    }

    for (size_t i = 0; i < al->length; ++i) {
        al->items[i] = buff[i];
    }

    return ARRAYLIST_OK;
}

AL_status array_list_copy(const ArrList *src, ArrList *dst) {
    if (!src || !dst) {
        return ARRAYLIST_ERR_WRONG_PTR;
    }

    if (src->capacity > dst->capacity) {
        return ARRAYLIST_ERR_SRC_LARGER_THAN_DST;
    }

    AL_status status = ARRAYLIST_OK;
    for (size_t i = 0; i < src->length; ++i) {
        if ((status = array_list_append(dst, src->items[i])) != ARRAYLIST_OK) {
            return status;
        }
    }

    return ARRAYLIST_OK;
}

size_t array_list_len(const ArrList *al) {
    if (!al) {
        return 0;
    }

    return al->length;
}

AL_status array_list_swap(ArrList *al, const size_t i1, const size_t i2) {
    if (!al) {
        return ARRAYLIST_ERR_WRONG_PTR;
    }

    if (i1 >= al->length || i2 >= al->length) {
        return ARRAYLIST_IDX_OUT_OF_RANGE;
    }

    int tmp = al->items[i1];
    al->items[i1] = al->items[i2];
    al->items[i2] = tmp;

    return ARRAYLIST_OK;
}

int array_list_get(ArrList *al, const size_t i) {
    if (!al) {
        return INT_MAX;
    }

    if (i >= al->length) {
        return INT_MAX;
    }

    return al->items[i];
}

AL_status array_list_remove(ArrList *al, const size_t i) {
    if (!al) {
        return ARRAYLIST_ERR_WRONG_PTR;
    }

    if (i >= al->length) {
        return ARRAYLIST_IDX_OUT_OF_RANGE;
    }

    for (size_t j = i; j < al->length - 1; ++j) {
        array_list_swap(al, j, j + 1);
    }

    al->length--;

    return ARRAYLIST_OK;
}

// this function has a problem (dont know what it is yet)
ArrList *_helper(ArrList *left, ArrList *right) {
    ArrList *sorted = array_list_init(left->length + right->length);
    if (!sorted) {
        return NULL;
    }

    size_t i = 0;
    size_t j = 0;

    while (i < left->length && j < right->length) {
        if (left->items[i] < right->items[j]) {
            array_list_append(sorted, left->items[i++]);
        } else {
            array_list_append(sorted, right->items[j++]);
        }
    }

    while (i < left->length) {
        array_list_append(sorted, left->items[i++]);
    }

    while (j < right->length) {
        array_list_append(sorted, right->items[j++]);
    }

    return sorted;
}

ArrList *sort(ArrList *al) {
    if (!al || al->length <= 1) {
        return al;
    }

    size_t mid = al->length / 2;

    ArrList *left = array_list_init(mid);
    ArrList *right = array_list_init(al->length - mid);

    if (!left || !right) {
        array_list_deinit(&left);
        array_list_deinit(&right);
        return NULL;
    }

    for (size_t i = 0; i < mid; ++i) {
        array_list_append(left, al->items[i]);
    }

    for (size_t i = mid; i < al->length; ++i) {
        array_list_append(right, al->items[i]);
    }

    left = sort(left);
    right = sort(right);

    ArrList *result = _helper(left, right);

    array_list_deinit(&left);
    array_list_deinit(&right);

    return result;
}
