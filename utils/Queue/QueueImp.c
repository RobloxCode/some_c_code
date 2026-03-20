#include "QueueImp.h"
#include <stdlib.h>
#include <stdio.h>

Queue *Queue_init(size_t cap) {
    Stack_status status = STACK_OK;

    Queue *queue = malloc(sizeof *queue);
    if (!queue)
        goto stack_cleanup;

    queue->push_stack = Stack_init(cap);
    if (!queue->push_stack)
        goto stack_cleanup;

    queue->pop_stack = Stack_init(cap);
    if (!queue->pop_stack)
        goto stack_cleanup;

    queue->status = status;
    return queue;

stack_cleanup:
    if (queue->push_stack)
        Stack_free(&queue->push_stack);

    if (queue->pop_stack)
        Stack_free(&queue->pop_stack);

    if (queue) {
        free(queue);
        queue = NULL;
    }

    if (status != STACK_OK)
        fprintf(stderr, "Error status: %d\n", status);

    return NULL;
}

void Queue_deinit(Queue **queue) {
    if (!queue || !*queue)
        return;

    Stack_free(&(*queue)->push_stack);
    Stack_free(&(*queue)->pop_stack);
    free(*queue);
    *queue = NULL;
}

void Queue_push(Queue *queue, int item) {
    if (!queue)
        return;

    Stack_push(queue->push_stack, item);
}

void Queue_pop(Queue *queue) {
    if (!queue)
        return;

    size_t stack_len = Stack_len(queue->push_stack);
    int popped_item = 0;

    for (size_t i = 0; i < stack_len; ++i) {
        Stack_pop(queue->push_stack, &popped_item);
        Stack_push(queue->pop_stack, popped_item);
    }

    Stack_pop(queue->pop_stack, &popped_item);

    stack_len = Stack_len(queue->pop_stack);
    for (size_t i = 0; i < stack_len; ++i) {
        Stack_pop(queue->pop_stack, &popped_item);
        Stack_push(queue->push_stack, popped_item);
    }
}

void Queue_println(Queue *queue) {
    if (!queue)
        return;

    Stack_println(queue->push_stack);
}
