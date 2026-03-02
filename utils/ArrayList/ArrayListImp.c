#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    int *items;
    size_t length;
    size_t _count;
} ArrayList;

ArrayList *ArrayList_create(const size_t init_len) {
    int *items = calloc(init_len, sizeof *items);
    if (!items) {
        return NULL;
    }

    ArrayList *al = malloc(sizeof *al);
    if (!al) {
        free(items);
        return NULL;
    }

    al->items = items;
    al->_count = init_len;
    al->length = 0;

    return al;
}

int ArrayList_append(ArrayList *al, const int item) {
    if (al->length + 1 >= al->_count) {
        size_t new_len = al->_count * 2;
        int *tmp = realloc(al->items, new_len * sizeof *al->items);
        if (!tmp) {
            return -1;
        }

        al->items = tmp;
        al->_count = new_len;
    }

    al->items[al->length] = item;
    al->length++;

    return 0;
}

int ArrayList_free(ArrayList **al) {
    if (!al || !*al) {
        return -1;
    }

    free((*al)->items);
    free(*al);
    *al = NULL;
    return 0;
}

void ArrayList_print(const ArrayList *al) {
    for (size_t i = 0; i < al->length; ++i) {
        printf("%d ", al->items[i]);
    }

    printf("\n");
}
