#include "SafeMalloc.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void *safe_malloc_imp(size_t size, const char *file, int line) {
    void *ptr = malloc(size);

    if (!ptr) {
        fprintf(stderr, "malloc failed at %s: %d\n", file, line);
        exit(EXIT_FAILURE);
    }

    return ptr;
}

void *safe_calloc_imp(size_t count, size_t size, const char *file, int line) {
    void *ptr = calloc(count, size);

    if (!ptr) {
        fprintf(stderr, "malloc failed at %s: %d\n", file, line);
        exit(EXIT_FAILURE);
    }

    return ptr;
}

#define safe_malloc(size) safe_malloc_imp(size, __FILE__, __LINE__)

#define safe_calloc(count, size)                                               \
    safe_calloc_imp(count, size, __FILE__, __LINE__)
