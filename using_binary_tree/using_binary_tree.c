#include "../utils/BinarySearchTree/BinarySearchTreeImp.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    BST_status status = BST_OK;
    BST *bst = BST_init();
    if (!bst)
        return EXIT_FAILURE;

    if ((status = BST_append(bst, 1)) != BST_OK)
        goto cleanup;

    if ((status = BST_append(bst, 2)) != BST_OK)
        goto cleanup;

    if ((status = BST_append(bst, 3)) != BST_OK)
        goto cleanup;

    if ((status = BST_append(bst, 4)) != BST_OK)
        goto cleanup;

    if ((status = BST_append(bst, 5)) != BST_OK)
        goto cleanup;

    if ((status = BST_append(bst, 10)) != BST_OK)
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

cleanup:
    BST_deinit(&bst);

    if (status != BST_OK) {
        fprintf(stderr, "Error status: %d\n", status);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

