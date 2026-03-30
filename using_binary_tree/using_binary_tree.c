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

    printf("preorder: ");
    if ((status = BST_print_pre(bst)) != BST_OK)
        goto cleanup;

    printf("\ninorder: ");
    if ((status = BST_print_ino(bst)) != BST_OK)
        goto cleanup;

    printf("\npostorder: ");
    if ((status = BST_print_pos(bst)) != BST_OK)
        goto cleanup;
    printf("\n");

    // deleting a leaf
    if ((status = BST_remove(bst, 6)) != BST_OK)
        goto cleanup;

    printf("preorder after deletion: ");
    if ((status = BST_print_pre(bst)) != BST_OK)
        goto cleanup;

cleanup:
    BST_deinit(&bst);

    if (status != BST_OK)
        fprintf(stderr, "Error status: %d\n", status);
}

int main(void) {
    test_BST();
    return EXIT_SUCCESS;
}

