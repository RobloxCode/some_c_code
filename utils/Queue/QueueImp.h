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

Queue *queue_init();
void queue_deinit(Queue **q);
void queue_push(Queue *q, int val);
void queue_pop(Queue *q);
void queue_println(Queue *q);

#endif
