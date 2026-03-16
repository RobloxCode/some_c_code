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
    STACK_ERR_EMPTY,
    STACK_ERR_OVERFLOW,
} Stack_status;

Stack *Stack_init(const size_t init_cap) {
    if (init_cap > SIZE_MAX / 10) {
        return NULL;
    }

    if (init_cap == 0) {
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
    if (!stack || !*stack) {
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
        if (stack->cap > SIZE_MAX / 2) {
            return STACK_ERR_OVERFLOW;
        }

        size_t new_cap = stack->cap * 2;
        if (new_cap > SIZE_MAX / 2) {
            return STACK_ERR_OVERFLOW;
        }

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
    if (!stack || !out) {
        return STACK_ERR_WRONG_PTR;
    }

    if (stack->len == 0) {
        return STACK_ERR_EMPTY;
    }

    *out = stack->items[--stack->len];
    return STACK_OK;
}

Stack_status Stack_top(const Stack *stack, int *out) {
    if (!stack || !out) {
        return STACK_ERR_WRONG_PTR;
    }

    if (stack->len == 0) {
        return STACK_ERR_EMPTY;
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

