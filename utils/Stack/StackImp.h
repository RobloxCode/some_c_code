#ifndef STACKIMP_H
#define STACKIMP_H
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

Stack *Stack_init(const size_t init_cap);
Stack_status Stack_free(Stack **stack);
Stack_status Stack_push(Stack *stack, const int item);
Stack_status Stack_pop(Stack *stack, int *out);
Stack_status Stack_top(const Stack *stack, int *out);
Stack_status Stack_println(const Stack *stack);
Stack_status Stack_clear(Stack *stack);
size_t Stack_len(Stack *stack);

#endif
