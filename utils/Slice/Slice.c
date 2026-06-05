#include "Slice.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void *i_slice_make(int *src, size_t srclen, size_t start, size_t end) {
    if (start > end || end == start || (end - start) > srclen) {
        return NULL;
    }

    iSlice *s = malloc(sizeof *s);
    if (!s) {
        return NULL;
    }

    s->len = end - start;
    s->items = src + start;

    return s;
}

void i_slice_deinit(iSlice **s) {
    free(*s);
    *s = NULL;
}

int i_slice_init(iSlice *s, int *src, size_t srclen, size_t start, size_t end) {
    if (start > end || end == start || (end - start) > srclen) {
        return 1;
    }

    s->len = end - start;
    s->items = src + start;

    return 0;
}

void i_slice_println(iSlice *s) {
    for (size_t i = 0; i < s->len; ++i) {
        printf("%d ", s->items[i]);
    }
    printf("\n");
}
