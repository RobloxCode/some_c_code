/*
 * get a list of primes using the Sieve of Eratosthenes
 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>

typedef struct {
    int *items;
    size_t length;
    size_t _count;
} ArrayList;

ArrayList *ArrayList_create(const size_t init_len);
int ArrayList_append(ArrayList *al, const int item);
int ArrayList_free(ArrayList **al);
void ArrayList_print(const ArrayList *al);

noreturn void display_err(const char *msg);
int is_prime(int num);
int int_sqrt(int num);
ArrayList *get_primes(int num);

int main(void) {
    ArrayList *al = get_primes(100);
    if (!al) {
        display_err("creating ArrayList");
    }

    ArrayList_print(al);

    ArrayList_free(&al);
    return 0;
}

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

noreturn void display_err(const char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
    exit(-1);
}

int int_sqrt(int num) {
    if (num < 0) {
        return 0;
    }

    if (num < 2) {
        return num;
    }

    int res = 0;
    for (int i = 2; i < num; ++i) {
        if (i * i == num) {
            return i;
        } else if (i * i >= num) {
            return res;
        } else {
            res = i;
        }
    }

    return res;
}

int is_prime(int num) {
    if (num < 0) {
        return 0;
    }

    for (int i = 2; i < int_sqrt(num) + 1; ++i) {
        if (num % i == 0) {
            return 0;
        }
    }

    return 1;
}

ArrayList *get_primes(int num) {
    ArrayList *al = ArrayList_create((size_t)num);
    if (!al) {
        return NULL;
    }

    for (int i = 2; i <= num; ++i) {
        if (is_prime(i)) {
            ArrayList_append(al, i);
        }
    }

    return al;
}
