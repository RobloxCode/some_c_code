#include <stdio.h>
#include <stdlib.h>
#include "../../utils/ArrayList/ArrayListImp.h"
#include <stddef.h>

ArrayList *_helper(ArrayList *left, ArrayList *right) {
    ArrayList *sorted = ArrayList_init(left->length + right->length);
    if (!sorted) return NULL;

    size_t i = 0, j = 0;

    while (i < left->length && j < right->length) {
        if (left->items[i] < right->items[j]) {
            ArrayList_append(sorted, left->items[i++]);
        } else {
            ArrayList_append(sorted, right->items[j++]);
        }
    }

    while (i < left->length)
        ArrayList_append(sorted, left->items[i++]);

    while (j < right->length)
        ArrayList_append(sorted, right->items[j++]);

    return sorted;
}
ArrayList *sort(ArrayList *al) {
    if (!al || al->length <= 1)
        return al;

    size_t mid = al->length / 2;

    ArrayList *left = ArrayList_init(mid);
    ArrayList *right = ArrayList_init(al->length - mid);

    if (!left || !right) {
        ArrayList_deinit(&left);
        ArrayList_deinit(&right);
        return NULL;
    }

    for (size_t i = 0; i < mid; ++i)
        ArrayList_append(left, al->items[i]);

    for (size_t i = mid; i < al->length; ++i)
        ArrayList_append(right, al->items[i]);

    left = sort(left);
    right = sort(right);

    ArrayList *result = _helper(left, right);

    ArrayList_deinit(&left);
    ArrayList_deinit(&right);

    return result;
}

// ArrayList *_helper(ArrayList *left, ArrayList *right) {
//     ArrayList *sorted = ArrayList_init(left->length + right->length);
//     if (!sorted)
//         return NULL;
//
//     size_t i = 0;
//     size_t j = 0;
//
//     while (i < left->length && j < right->length) {
//         if (left->items[i] < right->items[j])
//             ArrayList_append(sorted, left->items[i++]);
//         else
//             ArrayList_append(sorted, right->items[j++]);
//     }
//
//     while (i < left->length)
//         ArrayList_append(sorted, left->items[i++]);
//
//     while (j < right->length)
//         ArrayList_append(sorted, right->items[j++]);
//
//     return sorted;
// }
//
// ArrayList *sort(ArrayList *al) {
//     if (!al || al->length <= 1)
//         return al;
//
//     size_t mid = al->length / 2;
//
//     ArrayList *left = ArrayList_init(mid);
//     ArrayList *right = ArrayList_init(al->length - mid);
//
//     if (!left || !right) {
//         ArrayList_deinit(&left);
//         ArrayList_deinit(&right);
//         return NULL;
//     }
//
//     for (size_t i = 0; i < mid; ++i)
//         ArrayList_append(left, al->items[i]);
//
//     for (size_t i = mid; i < al->length; ++i)
//         ArrayList_append(right, al->items[i]);
//
//     left = sort(left);
//     right = sort(right);
//
//     ArrayList *result = _helper(left, right);
//
//     ArrayList_deinit(&left);
//     ArrayList_deinit(&right);
//
//     return result;
// }
//

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

    ArrayList_println(data);

    if ((status = ArrayList_swap(data, 0, ArrayList_len(data)-1)) != ARRAYLIST_OK)
        goto cleanup;

    ArrayList_println(data);

    if ((status = ArrayList_remove(data, 0)) != ARRAYLIST_OK)
        goto cleanup;

    ArrayList_println(data);

    if ((status = ArrayList_remove(data, ArrayList_len(data) - 1)) != ARRAYLIST_OK)
        goto cleanup;

    if ((status = ArrayList_remove(data, ArrayList_len(data) - 1)) != ARRAYLIST_OK)
        goto cleanup;

    ArrayList_println(data);
    ArrayList *sorted = ArrayList_init(data->length);
    if (!sorted)
        goto cleanup;

    sorted = sort(data);
    ArrayList_println(sorted);

cleanup:
    ArrayList_deinit(&data);
    ArrayList_deinit(&data2);
    ArrayList_deinit(&sorted);

    if (status != ARRAYLIST_OK)
        fprintf(stderr, "Error status: %d\n", status);

    return;
}

int main(void) {
    test_ArrayList();
    return EXIT_SUCCESS;
}
