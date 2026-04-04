#ifndef ARRAYLISTIMP_H
#define ARRAYLISTIMP_H
#include <stddef.h>

typedef enum {
    ARRAYLIST_OK,
    ARRAYLIST_ERR_WRONG_PTR,
    ARRAYLIST_ERR_REALLOC,
    ARRAYLIST_ERR_OVERFLOW,
    ARRAYLIST_ERR_SRC_LARGER_THAN_DST,
    ARRAYLIST_IDX_OUT_OF_RANGE,
} ArrayList_status;

typedef struct {
    int *items;
    size_t length;
    size_t capacity;
} ArrayList;

ArrayList *ArrayList_init(const size_t cap);
ArrayList_status ArrayList_append(ArrayList *al, const int item);
ArrayList_status ArrayList_deinit(ArrayList **al);
ArrayList_status ArrayList_println(const ArrayList *al);
ArrayList_status ArrayList_reverse(ArrayList *al);
ArrayList_status ArrayList_copy(const ArrayList *src, ArrayList *dst);
ArrayList_status ArrayList_remove(ArrayList *al, const size_t i);
size_t ArrayList_len(const ArrayList *al);
ArrayList_status ArrayList_swap(
    ArrayList *al,
    const size_t i1,
    const size_t i2
);
int ArrayList_get(ArrayList *al, const size_t i);

#endif

