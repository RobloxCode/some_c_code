#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    int *items;
    size_t len;
    size_t cap;
} Stack;

typedef enum {
    STACK_OK,
    STACK_ERR_WRONG_PTR,
    STACK_ERR_REALLOC,
    STACK_ERR_EMTPY,
} Stack_status;

Stack *Stack_init(const size_t init_cap);
Stack_status Stack_free(Stack **stack);
Stack_status Stack_push(Stack *stack, const int item);
Stack_status Stack_pop(Stack *stack, int *out);
Stack_status Stack_top(Stack *stack, int *out);
Stack_status Stack_println(const Stack *stack);

int main(void) {
    const size_t stack_init_cap = 3;
    Stack_status status = STACK_OK;
    int outval = 0;
    Stack *s = Stack_init(stack_init_cap);
    if (!s) {
        return EXIT_FAILURE;
    }

    if ((status = Stack_push(s, 1)) != STACK_OK)
        goto cleanup;

    if ((status = Stack_push(s, 2)) != STACK_OK)
        goto cleanup;

    if ((status = Stack_push(s, 3)) != STACK_OK)
        goto cleanup;

    if ((status = Stack_push(s, 4)) != STACK_OK)
        goto cleanup;

    if ((status = Stack_println(s)) != STACK_OK)
        goto cleanup;

    if ((status = Stack_pop(s, &outval)) != STACK_OK)
        goto cleanup;

    printf("out: %d\n", outval);

    if ((status = Stack_println(s)) != STACK_OK)
        goto cleanup;

    if ((status = Stack_top(s, &outval)) != STACK_OK)
        goto cleanup;

    printf("out: %d\n", outval);

    if ((status = Stack_println(s)) != STACK_OK)
        goto cleanup;

    cleanup:
    Stack_free(&s);
    if (status != STACK_OK) {
        printf("Error Status: %d\n", status);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

Stack *Stack_init(const size_t init_cap) {
    if (init_cap > SIZE_MAX / 10) {
        return NULL;
    }

    int *items = calloc(init_cap, sizeof *items);
    if (!items) {
        return NULL;
    }

    Stack *stack = malloc(sizeof *stack);
    if (!stack) {
        free(items);
        return NULL;
    }

    stack->items = items;
    stack->len = 0;
    stack->cap = init_cap;
    return stack;
}

Stack_status Stack_free(Stack **stack) {
    if (!stack) {
        return STACK_ERR_WRONG_PTR;
    }

    free((*stack)->items);
    free(*stack);
    *stack = NULL;
    return STACK_OK;
}

Stack_status Stack_push(Stack *stack, const int item) {
    if (!stack) {
        return STACK_ERR_WRONG_PTR;
    }

    if (stack->len >= stack->cap) {
        size_t new_cap = stack->cap * 2;
        int *tmp = realloc(stack->items, new_cap * sizeof *stack->items);
        if (!tmp) {
            return STACK_ERR_REALLOC;
        }

        stack->items = tmp;
        stack->cap = new_cap;
    }

    stack->items[stack->len++] = item;
    return STACK_OK;
}

Stack_status Stack_pop(Stack *stack, int *out) {
    if (!stack) {
        return STACK_ERR_WRONG_PTR;
    }

    if (stack->len == 0) {
        return STACK_ERR_EMTPY;
    }

    *out = stack->items[stack->len - 1];
    stack->items[stack->len - 1] = 0;
    stack->len--;
    return STACK_OK;
}

Stack_status Stack_top(Stack *stack, int *out) {
    if (!stack || !out) {
        return STACK_ERR_WRONG_PTR;
    }

    *out = stack->items[stack->len - 1];
    return STACK_OK;
}

Stack_status Stack_println(const Stack *stack) {
    if (!stack) {
        return STACK_ERR_WRONG_PTR;
    }

    for (size_t i = 0; i < stack->len; ++i) {
        printf("%d ", stack->items[i]);
    }
    printf("\n");

    return STACK_OK;
}

