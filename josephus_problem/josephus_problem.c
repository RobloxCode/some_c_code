#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node *next;
} Node;

typedef struct {
    Node *start;
    size_t len;
} CircularList;

CircularList *CircularList_init();
void CircularList_deinit(CircularList **cl);
void CircularList_push(CircularList *cl, int val);
void CircularList_print(CircularList *cl);

int main(void) {
    CircularList *cl = CircularList_init();
    if (!cl)
        return EXIT_FAILURE;

    CircularList_push(cl, 1);
    CircularList_push(cl, 2);
    // CircularList_print(cl);
    printf("%zu\n", cl->len);
    CircularList_deinit(&cl);

    return EXIT_SUCCESS;
}

CircularList *CircularList_init() {
    CircularList *cl = malloc(sizeof *cl);
    if (!cl)
        return NULL;

    cl->len = 0;
    cl->start = NULL;

    return cl;
}

void CircularList_deinit(CircularList **cl) {
    if (!cl || !*cl)
        return;

    if (!(*cl)->start)
        return;

    Node *cur = (*cl)->start;
    Node *del = NULL;

    for (size_t i = 0; i < (*cl)->len; ++i) {
        del = cur;
        cur = cur->next;
        free(del);
    }

    free(*cl);
    *cl = NULL;
}

void CircularList_push(CircularList *cl, int val) {
    if (!cl)
        return;

    if (!cl->start) {
        Node *new = malloc(sizeof *new);
        if (!new)
            return;

        new->val = val;
        new->next = NULL;
        cl->start = new;
        cl->len++;
        return;
    }

    Node *last = cl->start;
    Node *new = malloc(sizeof *new);
    if (!new)
        return;

    new->val = val;
    new->next = cl->start;

    if (!last->next) {
        last->next = cl->start;
        cl->len++;
        return;
    }

    for (size_t i = 0; i < cl->len; ++i) {
        last = last->next;
    }

    last->next = new;
    cl->len++;
}

void CircularList_print(CircularList *cl) {
    if (!cl)
        return;

    Node *cur = cl->start;
    while (cur) {
        printf("%d\n", cur->val);
        cur = cur->next;
    }
}
