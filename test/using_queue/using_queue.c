#include <stdio.h>
#include <stdlib.h>
#include "../utils/Queue/QueueImp.h"

int main(void) {
    Queue *queue = Queue_init(4);
    if (!queue)
        return EXIT_FAILURE;

    Queue_push(queue, 1);
    Queue_push(queue, 2);
    Queue_push(queue, 3);
    Queue_push(queue, 4);
    Queue_push(queue, 5);
    Queue_push(queue, 6);
    Queue_push(queue, 7);

    Queue_println(queue);

    printf("pop from the queue\n");
    Queue_pop(queue);
    Queue_println(queue);

    Queue_pop(queue);
    Queue_println(queue);

    Queue_deinit(&queue);

    return EXIT_SUCCESS;
}

