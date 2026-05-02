#include "QueueImp.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

Queue *Queue_init()
{
    Queue *q = malloc(sizeof *q);
    if (!q)
        return NULL;

    q->len = 0;
    q->start = NULL;

    return q;
}

void Queue_deinit(Queue **q)
{
    if (!q || !*q)
        return;

    if (!(*q)->start)
        return;

    QueueNode *to_del = NULL;
    QueueNode *cur = (*q)->start;

    while (cur) {
        to_del = cur;
        cur = cur->next;
        free(to_del);
    }

    free(*q);
    *q = NULL;
}

void Queue_push(Queue *q, int val)
{
    if (!q)
        return;

    QueueNode *new_node = malloc(sizeof *new_node);
    new_node->next = NULL;
    new_node->val = val;

    if (!q->start) {
        q->start = new_node;
        q->len++;
        return;
    }

    QueueNode *cur = q->start;

    while (cur->next)
        cur = cur->next;

    cur->next = new_node;
    q->len++;
}

void Queue_pop(Queue *q)
{
    if (!q)
        return;

    if (!q->start || !q->start->next)
        return;

    QueueNode *to_del = q->start;
    q->start = q->start->next;

    free(to_del);
    q->len--;
}

void Queue_println(Queue *q)
{
    if (!q)
        return;

    QueueNode *cur = q->start;

    while (cur) {
        printf("%d ", cur->val);
        cur = cur->next;
    }

    printf("\n");
}
