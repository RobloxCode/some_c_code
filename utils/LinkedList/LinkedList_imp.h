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
} LinkedList_status;

LinkedList *LinkedList_init(void);
LinkedList_status LinkedList_deinit(LinkedList **ll);
LinkedList_status LinkedList_append(LinkedList *ll, const int val);
LinkedList_status LinkedList_remove(LinkedList *ll, const size_t idx);
LinkedList_status LinkedList_println(LinkedList *ll);
LinkedList_status LinkedList_reverse(LinkedList *ll);
size_t LinkedList_len(LinkedList *ll);

#endif
