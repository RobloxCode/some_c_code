#include "../utils/BinarySearchTree/BinarySearchTreeImp.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void test_BST(void) {
    BST_status status = BST_OK;
    BST *bst = BST_init();
    if (!bst)
        return;

    if ((status = BST_append(bst, 10)) != BST_OK)
        goto cleanup;

    if ((status = BST_append(bst, 5)) != BST_OK)
        goto cleanup;

    if ((status = BST_append(bst, 15)) != BST_OK)
        goto cleanup;

    if ((status = BST_append(bst, 6)) != BST_OK)
        goto cleanup;

    if ((status = BST_append(bst, 3)) != BST_OK)
        goto cleanup;

    if ((status = BST_append(bst, 11)) != BST_OK)
        goto cleanup;

    if ((status = BST_append(bst, 17)) != BST_OK)
        goto cleanup;

    if ((status = BST_append(bst, 7)) != BST_OK)
        goto cleanup;

    if ((status = BST_append(bst, 16)) != BST_OK)
        goto cleanup;

    if ((status = BST_println_pos(bst)) != BST_OK)
        goto cleanup;

    if ((status = BST_remove(bst, 6)) != BST_OK)
        goto cleanup;

    if ((status = BST_remove(bst, 16)) != BST_OK)
        goto cleanup;

    if ((status = BST_remove(bst, 5)) != BST_OK)
        goto cleanup;

    if ((status = BST_remove(bst, 10)) != BST_OK)
        goto cleanup;

    if ((status = BST_remove_rec(bst, 15)) != BST_OK)
        goto cleanup;

    if ((status = BST_println_pos(bst)) != BST_OK)
        goto cleanup;

    int min = 0;
    if ((status = BST_get_min(bst, &min)) != BST_OK)
        goto cleanup;

    printf("min value: %d\n", min);

cleanup:
    BST_deinit(&bst);

    if (status != BST_OK)
        fprintf(stderr, "Error status: %d\n", status);
}

int main(void) {
    test_BST();
    return EXIT_SUCCESS;
}

