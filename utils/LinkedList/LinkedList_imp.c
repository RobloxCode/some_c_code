#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

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
LinkedList *LinkedList_init(void) {
    LinkedList *ll = malloc(sizeof *ll);
    if (!ll)
        return NULL;

    ll->start = NULL;
    ll->len = 0;
    return ll;
}

LinkedList_status LinkedList_deinit(LinkedList **ll) {
    if (!ll)
        return LL_ERR_WRONG_PTR;

    if (!(*ll)->start) {
        free(*ll);
        return LL_OK;
    }

    Node *cur = (*ll)->start;
    while (cur) {
        Node *to_del = cur;
        cur = cur->next;
        free(to_del);
    }

    free(*ll);
    *ll = NULL;
    return LL_OK;
}

LinkedList_status LinkedList_append(LinkedList *ll, const int val) {
    if (!ll)
        return LL_ERR_WRONG_PTR;

    Node *new = malloc(sizeof *new);
    if (!new)
        return LL_ERR_MALLOC;

    new->val = val;
    new->next = NULL;

    if (!ll->start) {
        ll->start = new;
        ll->len++;
        return LL_OK;
    }

    Node *cur = ll->start;
    while (cur->next)
        cur = cur->next;

    cur->next = new;
    ll->len++;
    return LL_OK;
}

LinkedList_status LinkedList_remove(LinkedList *ll, const size_t idx) {
    if (!ll)
        return LL_ERR_WRONG_PTR;

    if (idx >= ll->len)
        return LL_ERR_IDX_OUT_OF_RANGE;

    Node *del = NULL;
    Node* cur = ll->start;

    if (idx == 0) {
        del = ll->start;
        ll->start = del->next;

        goto free_node;
    }

    for (size_t i = 0; i < idx - 1; ++i)
        cur = cur->next;

    del = cur->next;
    cur->next = del->next;

free_node:
    free(del);
    ll->len--;
    return LL_OK;
}

LinkedList_status LinkedList_println(LinkedList *ll) {
    if (!ll)
        return LL_ERR_WRONG_PTR;

    Node *cur = ll->start;
    while (cur) {
        printf("%d ", cur->val);
        cur = cur->next;
    }

    printf("\n");
    return LL_OK;
}

LinkedList_status LinkedList_reverse(LinkedList *ll) {
    if (!ll)
        return LL_ERR_WRONG_PTR;

    return LL_OK;
}

size_t LinkedList_len(LinkedList *ll) {
    if (!ll)
        return 0;

    return ll->len;
}
