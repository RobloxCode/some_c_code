#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct BSTNode {
    int val;
    struct BSTNode *left_node;
    struct BSTNode *right_node;
} BSTNode;

typedef struct {
    BSTNode *root;
    size_t height;
} BST;

BST *BST_init();
void BST_deinit(BST **bst);
void BST_append(BST *bst, int val);
void BST_remove(BST *bst);

int main(void) {
    return EXIT_SUCCESS;
}

BST *BST_init() {
    BST *bst = malloc(sizeof *bst);
    if (!bst)
        return NULL;

    bst->root = NULL;
    bst->height = 0;

    return bst;
}

void BST_deinit(BST **bst) {
    if (!bst || !*bst)
        return;

    BSTNode *cur = (*bst)->root;
    if (!cur)
        return;

    if (!cur->left_node || !cur->right_node) {
        *bst = NULL;
        free(*bst);
        return;
    }


}

void BST_append(BST *bst, int val) {
    if (!bst)
        return;

    BSTNode *new = malloc(sizeof *new);
    if (!new)
        return;

    new->val = val;
    new->left_node = NULL;
    new->right_node = NULL;

    if (!bst->root) {
        bst->root = new;
        return;
    }

    BSTNode *cur = bst->root;

    for (;;) {
        if (val == cur->val) {
            free(new);
            return;
        }

        if (val < cur->val) {
            if (!cur->left_node) {
                cur->left_node = new;
                return;
            }

            cur = cur->left_node;
        }

        if (val > cur->val) {
            if (!cur->right_node) {
                cur->right_node = new;
                return;
            }

            cur = cur->right_node;
        }
    }
}

void BST_remove(BST *bst);
