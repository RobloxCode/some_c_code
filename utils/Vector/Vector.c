/*
 * vec.c — implementation of the raw (type-erased) vector helpers.
 *
 * Compile alongside your project:
 *   cc -o myapp main.c Vector.c
 */

#include "Vector.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

int vec_raw_reserve(void **data, size_t *cap, size_t new_cap,
                    size_t elem_size) {
    if (new_cap <= *cap) {
        return 1;
    }

    size_t c = (*cap == 0) ? VEC_INIT_CAP : *cap;
    while (c < new_cap) {
        c *= VEC_GROWTH;
    }

    void *block = realloc(*data, c * elem_size);
    if (!block) {
        return 0;
    }

    *data = block;
    *cap = c;
    return 1;
}

int vec_raw_push(void **data, size_t *size, size_t *cap, size_t elem_size,
                 const void *elem) {
    if (!vec_raw_reserve(data, cap, *size + 1, elem_size)) {
        return 0;
    }
    memcpy((char *)*data + (*size) * elem_size, elem, elem_size);
    (*size)++;
    return 1;
}

int vec_raw_insert(void **data, size_t *size, size_t *cap, size_t elem_size,
                   size_t i, const void *elem) {
    if (i > *size) {
        return 0;
    }
    if (!vec_raw_reserve(data, cap, *size + 1, elem_size)) {
        return 0;
    }

    char *base = (char *)*data;
    memmove(base + (i + 1) * elem_size, base + i * elem_size,
            (*size - i) * elem_size);
    memcpy(base + i * elem_size, elem, elem_size);
    (*size)++;
    return 1;
}

int vec_raw_remove(void **data, size_t *size, size_t elem_size, size_t i) {
    if (i >= *size) {
        return 0;
    }
    char *base = (char *)*data;
    memmove(base + i * elem_size, base + (i + 1) * elem_size,
            (*size - i - 1) * elem_size);
    (*size)--;
    return 1;
}

int vec_raw_swap_remove(void *data, size_t *size, size_t elem_size, size_t i) {
    if (i >= *size) {
        return 0;
    }
    if (i != *size - 1) {
        memcpy((char *)data + i * elem_size,
               (char *)data + (*size - 1) * elem_size, elem_size);
    }
    (*size)--;
    return 1;
}

void *vec_raw_at(void *data, size_t size, size_t elem_size, size_t i) {
    assert(i < size);
    return (char *)data + i * elem_size;
}

int vec_raw_shrink(void **data, size_t *cap, size_t size, size_t elem_size) {
    size_t target = (size < VEC_MIN_CAP) ? VEC_MIN_CAP : size;
    if (target == *cap) {
        return 1;
    }

    void *block = realloc(*data, target * elem_size);
    if (!block && target > 0) {
        return 0;
    }

    *data = block;
    *cap = target;
    return 1;
}
