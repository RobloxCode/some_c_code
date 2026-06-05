#include "../../utils/Stack/StackImp.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const size_t stack_init_cap = 3;
    Stack_status status = STACK_OK;
    int outval = 0;
    Stack *s = stack_init(stack_init_cap);
    if (!s) {
        return EXIT_FAILURE;
    }

    if ((status = stack_push(s, 1)) != STACK_OK) {
        goto cleanup;
    }

    if ((status = stack_push(s, 2)) != STACK_OK) {
        goto cleanup;
    }

    if ((status = stack_push(s, 3)) != STACK_OK) {
        goto cleanup;
    }

    if ((status = stack_push(s, 4)) != STACK_OK) {
        goto cleanup;
    }

    if ((status = stack_println(s)) != STACK_OK) {
        goto cleanup;
    }

    if ((status = stack_pop(s, &outval)) != STACK_OK) {
        goto cleanup;
    }

    printf("out: %d\n", outval);

    if ((status = stack_println(s)) != STACK_OK) {
        goto cleanup;
    }

    if ((status = stack_top(s, &outval)) != STACK_OK) {
        goto cleanup;
    }

    printf("out: %d\n", outval);

    if ((status = stack_println(s)) != STACK_OK) {
        goto cleanup;
    }

cleanup:
    stack_free(&s);
    if (status != STACK_OK) {
        printf("Error Status: %d\n", status);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
