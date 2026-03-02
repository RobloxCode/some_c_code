/*
 * get a list of primes using the Sieve of Eratosthenes
 */

#include <stdio.h>
#include "../utils/ArrayList/ArrayListImp.h"
#include <stdlib.h>
#include <stdnoreturn.h>

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
    return EXIT_SUCCESS;
}

noreturn void display_err(const char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
    exit(EXIT_FAILURE);
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
