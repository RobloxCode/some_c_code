#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "../utils/LinkedList/LinkedList_imp.h"

int main(void) {
    LinkedList_status status = LL_OK;
    LinkedList *ll = LinkedList_init();
    if (!ll) {
        return EXIT_FAILURE;
    }

    for (int i = 1; i <= 6; ++i) {
        if ((status = LinkedList_append(ll, i)) != LL_OK)
            goto cleanup;
    }

    if ((status = LinkedList_println(ll)) != LL_OK)
        goto cleanup;

    if ((status = LinkedList_remove(ll, 2)) != LL_OK)
        goto cleanup;

    if ((status = LinkedList_println(ll)) != LL_OK)
        goto cleanup;

    if ((status = LinkedList_remove(ll, 0)) != LL_OK)
        goto cleanup;

    if ((status = LinkedList_println(ll)) != LL_OK)
        goto cleanup;

    if ((status = LinkedList_remove(ll, LinkedList_len(ll) - 1)) != LL_OK)
        goto cleanup;

    if ((status = LinkedList_println(ll)) != LL_OK)
        goto cleanup;

    if ((status = LinkedList_remove(ll, 0)) != LL_OK)
        goto cleanup;

    if ((status = LinkedList_println(ll)) != LL_OK)
        goto cleanup;

cleanup:
    LinkedList_deinit(&ll);

    if (status != LL_OK) {
        printf("Error status: %d\n", status);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

