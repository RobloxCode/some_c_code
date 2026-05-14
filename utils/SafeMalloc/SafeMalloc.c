#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void *safe_malloc_imp(size_t size, const char *file, int line)
{
    void *ptr = malloc(size);

    if (!ptr) {
        fprintf(stderr,
                "malloc failed at %s: %d\n",
                file,
                line);
        exit(EXIT_FAILURE);
    }

    return ptr;
}

void *safe_calloc_imp(size_t count,
                      size_t size,
                      const char *file,
                      int line)
{
    void *ptr = calloc(count, size);

    if (!ptr) {
        fprintf(stderr,
                "malloc failed at %s: %d\n",
                file,
                line);
        exit(EXIT_FAILURE);
    }

    return ptr;
}

#define safe_malloc(size) \
    safe_malloc_imp(size, __FILE__, __LINE__)

#define safe_calloc(count, size) \
    safe_calloc_imp(count, size, __FILE__, __LINE__)

int main(void)
{
    float *grades = safe_malloc(10 * sizeof *grades);
    int *nums = safe_calloc(10, sizeof *nums);

    free(grades);
    free(nums);
    return EXIT_SUCCESS;
}

