#ifndef QUEUEIMP_H
#define QUEUEIMP_H

#include <stddef.h>

typedef struct QueueNode {
    int val;
    struct QueueNode *next;
} QueueNode;

typedef struct {
    QueueNode *start;
    size_t len;
} Queue;

Queue *Queue_init();
void Queue_deinit(Queue **q);
void Queue_push(Queue *q, int val);
void Queue_pop(Queue *q);
void Queue_println(Queue *q);

#endif
