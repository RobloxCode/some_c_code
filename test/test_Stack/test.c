#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../utils/Stack/StackImp.h"

int main(void) {
    int pop_val = 0;
    const size_t stack_init_cap = 10;
    Stack_status status = STACK_OK;
    Stack *s = Stack_init(stack_init_cap);
    if (!s)
        return EXIT_FAILURE;

    puts("empty stack:");
    if ((status = Stack_println(s)) != STACK_OK)
        goto cleanup;

    // pop when it is still empty
    // if ((status = Stack_top(s, &pop_val)) != STACK_OK)
    //     goto cleanup;
    // printf("item from the top: %d\n", pop_val);

    for (int i = 1; i <= 10; ++i) {
        if ((status = Stack_push(s, i)) != STACK_OK)
            goto cleanup;
    }

    if ((status = Stack_println(s)) != STACK_OK)
        goto cleanup;

    if ((status = Stack_pop(s, &pop_val)) != STACK_OK)
        goto cleanup;
    printf("popped items: %d\n", pop_val);

    if ((status = Stack_println(s)) != STACK_OK)
        goto cleanup;

    if ((status = Stack_top(s, &pop_val)) != STACK_OK)
        goto cleanup;
    printf("item from the top: %d\n", pop_val);

    if ((status = Stack_println(s)) != STACK_OK)
        goto cleanup;

    if ((status = Stack_clear(s)) != STACK_OK)
        goto cleanup;

    puts("empty stack:");
    if ((status = Stack_println(s)) != STACK_OK)
        goto cleanup;

    if ((status = Stack_push(s, 1)) != STACK_OK)
        goto cleanup;

    if ((status = Stack_push(s, 2)) != STACK_OK)
        goto cleanup;

    if ((status = Stack_println(s)) != STACK_OK)
        goto cleanup;

cleanup:
    Stack_free(&s);

    if (status != STACK_OK) {
        fprintf(stderr, "Error status: %d\n", status);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
