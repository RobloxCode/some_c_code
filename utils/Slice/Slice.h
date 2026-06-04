#ifndef SLICE_H
#define SLICE_H

#include <stddef.h>

typedef struct {
    int *items;
    size_t len;
} iSlice;

void *iSlice_make(int *src, size_t srclen, size_t start, size_t end);
void iSlice_deinit(iSlice **s);
int iSlice_init(iSlice *s, int *src, size_t srclen, size_t start, size_t end);
void iSlice_println(iSlice *s);

#endif
