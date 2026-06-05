#ifndef SLICE_H
#define SLICE_H

#include <stddef.h>

typedef struct {
    int *items;
    size_t len;
} iSlice;

void *i_slice_make(int *src, size_t srclen, size_t start, size_t end);
void i_slice_deinit(iSlice **s);
int i_slice_init(iSlice *s, int *src, size_t srclen, size_t start, size_t end);
void i_slice_println(iSlice *s);

#endif
