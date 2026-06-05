#include "../../utils/Queue/QueueImp.h"

#include <stdlib.h>

int main(void) {
    Queue *q = queue_init();
    if (!q) {
        return EXIT_FAILURE;
    }

    queue_push(q, 1);
    queue_push(q, 2);
    queue_push(q, 3);
    queue_push(q, 4);

    queue_println(q);

    queue_pop(q);
    queue_println(q);

    queue_pop(q);
    queue_println(q);

    queue_deinit(&q);

    return EXIT_SUCCESS;
}
