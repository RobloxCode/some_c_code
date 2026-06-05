#ifndef LINKEDLIST_IMP_H
#define LINKEDLIST_IMP_H
#include <stddef.h>

typedef struct Node {
    int val;
    struct Node *next;
} Node;

typedef struct {
    Node *start;
    size_t len;
} LinkedList;

typedef enum {
    LL_OK,
    LL_ERR_WRONG_PTR,
    LL_ERR_MALLOC,
    LL_ERR_IDX_OUT_OF_RANGE,
    LL_ERR_OVERFLOW,
    LL_ERR_EMPTY,
    LL_ERR_VALUE_NOT_FOUND,
} LL_status;

LinkedList *ll_init(void);
LL_status ll_deinit(LinkedList **ll);
LL_status ll_append(LinkedList *ll, const int val);
LL_status ll_remove(LinkedList *ll, const size_t idx);
LL_status ll_println(LinkedList *ll);
LL_status ll_reverse(LinkedList *ll);
size_t ll_len(LinkedList *ll);
LL_status ll_to_arr(const LinkedList *ll, int *dst, const size_t dst_len);
LinkedList *arr_to_ll(const int *arr, const size_t arr_len);
LL_status ll_search(const LinkedList *ll, const int val, size_t *out);

#endif
