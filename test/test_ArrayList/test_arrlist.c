#include "../../utils/ArrayList/ArrayListImp.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void test_ArrList(void) {
    const size_t data_len = 20;
    AL_status status = ARRAYLIST_OK;
    ArrList *data = array_list_init(data_len);
    if (!data) {
        return;
    }

    for (size_t i = 1; i <= 20; ++i) {
        if ((status = array_list_append(data, (int)i)) != ARRAYLIST_OK) {
            goto cleanup;
        }
    }

    array_list_println(data);

    if ((status = array_list_reverse(data)) != ARRAYLIST_OK) {
        goto cleanup;
    }

    array_list_println(data);

    ArrList *data2 = array_list_init(data->length);
    if (!data2) {
        goto cleanup;
    }

    if ((status = array_list_copy(data, data2)) != ARRAYLIST_OK) {
        goto cleanup;
    }

    puts("data2: ");
    array_list_println(data2);

    array_list_println(data);

    if ((status = array_list_swap(data, 0, array_list_len(data) - 1))
        != ARRAYLIST_OK) {
        goto cleanup;
    }

    array_list_println(data);

    if ((status = array_list_remove(data, 0)) != ARRAYLIST_OK) {
        goto cleanup;
    }

    array_list_println(data);

    if ((status = array_list_remove(data, array_list_len(data) - 1))
        != ARRAYLIST_OK) {
        goto cleanup;
    }

    if ((status = array_list_remove(data, array_list_len(data) - 1))
        != ARRAYLIST_OK) {
        goto cleanup;
    }

    array_list_println(data);
    ArrList *sorted = array_list_init(data->length);
    if (!sorted) {
        goto cleanup;
    }

    // sorted = sort(data);
    array_list_println(sorted);

cleanup:
    array_list_deinit(&data);
    array_list_deinit(&data2);
    array_list_deinit(&sorted);

    if (status != ARRAYLIST_OK) {
        fprintf(stderr, "Error status: %d\n", status);
    }

    return;
}

int main(void) {
    test_ArrList();
    return EXIT_SUCCESS;
}
