#ifndef SAFEMALLOC_H
#define SAFEMALLOC_H

#include <stddef.h>

void *safe_malloc_imp(size_t size, const char *file, int line);
void *safe_calloc_imp(size_t count, size_t size, const char *file, int line);

#define safe_malloc(size) safe_malloc_imp(size, __FILE__, __LINE__)

#define safe_calloc(count, size)                                               \
    safe_calloc_imp(count, size, __FILE__, __LINE__)

#endif
