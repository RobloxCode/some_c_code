#ifndef ARRAYLISTIMP_H
#define ARRAYLISTIMP_H
#include <stddef.h>

typedef enum {
    ARRAYLIST_OK,
    ARRAYLIST_ERR_WRONG_PTR,
    ARRAYLYST_ERR_REALLOC,
    ARRAYLIST_ERR_OVERFLOW,
} ArrayList_status;

typedef struct {
    int *items;
    size_t length;
    size_t capacity;
} ArrayList;

ArrayList *ArrayList_create(size_t init_len);
ArrayList_status ArrayList_append(ArrayList *al, const int item);
ArrayList_status ArrayList_free(ArrayList **al);
ArrayList_status ArrayList_print(const ArrayList *al);
#endif

