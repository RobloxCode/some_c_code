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
} AL_status;

typedef struct {
    int *items;
    size_t length;
    size_t capacity;
} ArrList;

ArrList *array_list_init(const size_t cap);
AL_status array_list_append(ArrList *al, const int item);
AL_status array_list_deinit(ArrList **al);
AL_status array_list_println(const ArrList *al);
AL_status array_list_reverse(ArrList *al);
AL_status array_list_copy(const ArrList *src, ArrList *dst);
AL_status array_list_remove(ArrList *al, const size_t i);
size_t array_list_len(const ArrList *al);
AL_status array_list_swap(ArrList *al, const size_t i1, const size_t i2);
int array_list_get(ArrList *al, const size_t i);

#endif
