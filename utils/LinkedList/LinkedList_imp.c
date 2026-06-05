#include "LinkedList_imp.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

LinkedList *ll_init(void) {
    LinkedList *ll = malloc(sizeof *ll);
    if (!ll) {
        return NULL;
    }

    ll->start = NULL;
    ll->len = 0;
    return ll;
}

LL_status ll_deinit(LinkedList **ll) {
    if (!ll) {
        return LL_ERR_WRONG_PTR;
    }

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

LL_status ll_append(LinkedList *ll, const int val) {
    if (!ll) {
        return LL_ERR_WRONG_PTR;
    }

    Node *new = malloc(sizeof *new);
    if (!new) {
        return LL_ERR_MALLOC;
    }

    new->val = val;
    new->next = NULL;

    if (!ll->start) {
        ll->start = new;
        ll->len++;
        return LL_OK;
    }

    Node *cur = ll->start;
    while (cur->next) {
        cur = cur->next;
    }

    cur->next = new;
    ll->len++;
    return LL_OK;
}

LL_status ll_remove(LinkedList *ll, const size_t idx) {
    if (!ll) {
        return LL_ERR_WRONG_PTR;
    }

    if (idx >= ll->len) {
        return LL_ERR_IDX_OUT_OF_RANGE;
    }

    Node *del = NULL;
    Node *cur = ll->start;

    if (idx == 0) {
        del = ll->start;
        ll->start = del->next;

        goto free_node;
    }

    for (size_t i = 0; i < idx - 1; ++i) {
        cur = cur->next;
    }

    del = cur->next;
    cur->next = del->next;

free_node:
    free(del);
    ll->len--;
    return LL_OK;
}

LL_status ll_println(LinkedList *ll) {
    if (!ll) {
        return LL_ERR_WRONG_PTR;
    }

    Node *cur = ll->start;
    while (cur) {
        printf("%d ", cur->val);
        cur = cur->next;
    }

    printf("\n");
    return LL_OK;
}

LL_status ll_reverse(LinkedList *ll) {
    if (!ll) {
        return LL_ERR_WRONG_PTR;
    }

    Node *cur = ll->start;
    Node *before = NULL;

    while (cur) {
        Node *next = cur->next;
        cur->next = before;
        before = cur;
        cur = next;
    }

    ll->start = before;
    return LL_OK;
}

size_t ll_len(LinkedList *ll) {
    if (!ll) {
        return 0;
    }

    return ll->len;
}

LL_status ll_to_arr(const LinkedList *ll, int *dst, const size_t dst_len) {
    if (!ll || !dst) {
        return LL_ERR_WRONG_PTR;
    }

    if (dst_len > ll->len) {
        return LL_ERR_OVERFLOW;
    }

    if (!ll->start) {
        return LL_ERR_EMPTY;
    }

    Node *cur = ll->start;
    for (size_t i = 0; i < dst_len; ++i) {
        dst[i] = cur->val;
        cur = cur->next;
    }

    return LL_OK;
}

LinkedList *arr_to_ll(const int *arr, const size_t arr_len) {
    if (!arr) {
        return NULL;
    }

    LinkedList *new = ll_init();
    if (!new) {
        return NULL;
    }

    LL_status status = LL_OK;
    for (size_t i = 0; i < arr_len; ++i) {
        if ((status = ll_append(new, arr[i])) != LL_OK) {
            return NULL;
        }
    }

    return new;
}

LL_status ll_search(const LinkedList *ll, const int val, size_t *out) {
    if (!ll || !out) {
        return LL_ERR_WRONG_PTR;
    }

    if (ll->len == 0) {
        return LL_ERR_EMPTY;
    }

    Node *cur = ll->start;
    for (size_t i = 0; cur != NULL; ++i) {
        if (cur->val == val) {
            *out = i;
            return LL_OK;
        }
        cur = cur->next;
    }

    return LL_ERR_VALUE_NOT_FOUND;
}
