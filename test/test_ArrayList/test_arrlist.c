#include <stdio.h>
#include <stdlib.h>
#include "../../utils/ArrayList/ArrayListImp.h"
#include <stddef.h>

int main(void)
{
    const size_t data_len = 20;
    ArrayList_status status = ARRAYLIST_OK;
    ArrayList *data = ArrayList_init(data_len);
    if (!data)
        return EXIT_FAILURE;

    for (size_t i = 1; i <= 20; ++i) {
        if ((status = ArrayList_append(data, (int)i)) != ARRAYLIST_OK)
            goto cleanup;
    }

    ArrayList_println(data);
    if ((status = ArrayList_reverse(data)) != ARRAYLIST_OK)
        goto cleanup;

    ArrayList_println(data);

cleanup:
    ArrayList_deinit(&data);
    if (status != ARRAYLIST_OK) {
        fprintf(stderr, "Error status: %d", status);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
