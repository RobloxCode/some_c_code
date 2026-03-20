#ifndef QUEUEIMP_H
#define QUEUEIMP_H
#include "../Stack/StackImp.h"
#include <stddef.h>

typedef struct {
    Stack *push_stack;
    Stack *pop_stack;
    Stack_status status;
} Queue;

Queue *Queue_init(size_t cap);
void Queue_deinit(Queue **queue);
void Queue_push(Queue *queue, int item);
void Queue_pop(Queue *queue);
void Queue_println(Queue *queue);

#endif
