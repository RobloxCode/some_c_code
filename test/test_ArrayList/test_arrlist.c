#include <stdio.h>
#include <stdlib.h>
#include "../../utils/ArrayList/ArrayListImp.h"
#include <stddef.h>

void test_ArrayList(void) {
    const size_t data_len = 20;
    ArrayList_status status = ARRAYLIST_OK;
    ArrayList *data = ArrayList_init(data_len);
    if (!data)
        return;

    for (size_t i = 1; i <= 20; ++i) {
        if ((status = ArrayList_append(data, (int)i)) != ARRAYLIST_OK)
            goto cleanup;
    }

    ArrayList_println(data);

    if ((status = ArrayList_reverse(data)) != ARRAYLIST_OK)
        goto cleanup;

    ArrayList_println(data);

    ArrayList *data2 = ArrayList_init(data->length);
    if (!data2)
        goto cleanup;

    if ((status = ArrayList_copy(data, data2)) != ARRAYLIST_OK)
        goto cleanup;

    puts("data2: ");
    ArrayList_println(data2);

cleanup:
    ArrayList_deinit(&data);
    ArrayList_deinit(&data2);

    if (status != ARRAYLIST_OK)
        fprintf(stderr, "Error status: %d", status);

    return;
}

int main(void) {
    test_ArrayList();
    return EXIT_SUCCESS;
}
