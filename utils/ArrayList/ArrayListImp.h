#ifndef ARRAYLISTIMP_H
#define ARRAYLISTIMP_H
#include <stddef.h>

typedef struct {
    int *items;
    size_t length;
    size_t _count;
} ArrayList;

ArrayList *ArrayList_create(const size_t init_len);
int ArrayList_append(ArrayList *al, const int item);
int ArrayList_free(ArrayList **al);
void ArrayList_print(const ArrayList *al);
#endif

