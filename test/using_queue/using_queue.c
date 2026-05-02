#include <stdlib.h>
#include "../../utils/Queue/QueueImp.h"

int main(void) {
    Queue *q = Queue_init();
    if (!q)
        return EXIT_FAILURE;

    Queue_push(q, 1);
    Queue_push(q, 2);
    Queue_push(q, 3);
    Queue_push(q, 4);

    Queue_println(q);

    Queue_pop(q);
    Queue_println(q);

    Queue_pop(q);
    Queue_println(q);

    Queue_deinit(&q);

    return EXIT_SUCCESS;
}

