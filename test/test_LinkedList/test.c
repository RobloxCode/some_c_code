#include "../../utils/LinkedList/LinkedList_imp.h"

#include <stdio.h>
#include <stdlib.h>
#define ARR_LEN 16

int main(void) {
    int arr[ARR_LEN];
    LL_status status = LL_OK;
    LinkedList *ll = ll_init();
    if (!ll) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < ARR_LEN; ++i) {
        arr[i] = (int)i;
    }

    if ((status = ll_append(ll, 1)) != LL_OK) {
        goto cleanup;
    }

    if ((status = ll_append(ll, 2)) != LL_OK) {
        goto cleanup;
    }

    if ((status = ll_append(ll, 3)) != LL_OK) {
        goto cleanup;
    }

    if ((status = ll_append(ll, 4)) != LL_OK) {
        goto cleanup;
    }

    if ((status = ll_append(ll, 5)) != LL_OK) {
        goto cleanup;
    }

    if ((status = ll_println(ll)) != LL_OK) {
        goto cleanup;
    }

    if ((status = ll_to_arr(ll, arr, ll->len) != LL_OK)) {
        goto cleanup;
    }

    puts("array");
    for (size_t i = 0; i < ll_len(ll); ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    LinkedList *from_arr = arr_to_ll(arr, ARR_LEN);
    if (!from_arr) {
        goto cleanup;
    }

    puts("linked list copied from the arr");
    if ((status = ll_println(from_arr)) != LL_OK) {
        goto cleanup;
    }

    puts("list before reverse");
    if ((status = ll_println(ll)) != LL_OK) {
        goto cleanup;
    }

    if ((status = ll_reverse(ll)) != LL_OK) {
        goto cleanup;
    }

    puts("reversed");
    if ((status = ll_println(ll)) != LL_OK) {
        goto cleanup;
    }

    size_t idx = 0;
    int val_to_find = 5;
    if ((status = ll_search(ll, val_to_find, &idx)) != LL_OK) {
        goto cleanup;
    }

    printf("idx: %zu\nval: %d", idx, val_to_find);

cleanup:
    ll_deinit(&ll);
    ll_deinit(&from_arr);

    if (status != LL_OK) {
        fprintf(stderr, "Error status: %d\n", status);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
