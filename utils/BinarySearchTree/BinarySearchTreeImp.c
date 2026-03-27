#include "BinarySearchTreeImp.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

BSTNode *BSTNode_init(const int val) {
    BSTNode *bstnode = malloc(sizeof *bstnode);
    if (!bstnode)
        return NULL;

    bstnode->val = val;
    bstnode->left_child = NULL;
    bstnode->right_child = NULL;
    return bstnode;
}

void BSTNode_deinit(BSTNode **bstnode) {
    if (!bstnode || !*bstnode)
        return;

    free(*bstnode);
    *bstnode = NULL;
}

BST *BST_init(void) {
    BST *bst = malloc(sizeof *bst);
    if (!bst)
        return NULL;

    bst->root = NULL;
    bst->height = 0;

    return bst;
}

static void _free_node(BSTNode *node) {
    if (!node)
        return;

    _free_node(node->left_child);
    _free_node(node->right_child);
    BSTNode_deinit(&node);
}

BST_status BST_deinit(BST **bst) {
    if (!bst || !*bst)
        return BST_ERR_WRONG_PTR;

    _free_node((*bst)->root);
    free((*bst));
    *bst = NULL;

    return BST_OK;
}

BST_status BST_append(BST *bst, const int val) {
    if (!bst)
        return BST_ERR_WRONG_PTR;

    BSTNode *new = BSTNode_init(val);
    if (!new)
        return BST_ERR_INIT_NODE;

    if (!bst->root) {
        bst->root = new;
        return BST_OK;
    }

    BSTNode *cur = bst->root;

    while (1) {
        if (new->val == cur->val) {
            BSTNode_deinit(&new);
            return BST_ERR_REPEATED_VAL;
        } else if (new->val < cur->val) {
            if (!cur->left_child) {
                cur->left_child = new;
                return BST_OK;
            }

            cur = cur->left_child;
        } else {
            if (!cur->right_child) {
                cur->right_child = new;
                return BST_OK;
            }

            cur = cur->right_child;
        }
    }

}

static void _print_bstnode_pre(const BSTNode *node) {
    if (!node)
        return;

    printf("%d ", node->val);
    _print_bstnode_pre(node->left_child);
    _print_bstnode_pre(node->right_child);
}

BST_status BST_print_pre(const BST *bst) {
    if (!bst)
        return BST_ERR_WRONG_PTR;

    _print_bstnode_pre(bst->root);
    return BST_OK;
}

static void _print_bstnode_ino(const BSTNode *node) {
    if (!node)
        return;

    _print_bstnode_ino(node->left_child);
    printf("%d ", node->val);
    _print_bstnode_ino(node->right_child);
}

BST_status BST_print_ino(const BST *bst) {
    if (!bst)
        return BST_ERR_WRONG_PTR;

    _print_bstnode_ino(bst->root);
    return BST_OK;
}

static void _print_bstnode_pos(const BSTNode *node) {
    if (!node)
        return;

    _print_bstnode_pos(node->left_child);
    _print_bstnode_pos(node->right_child);
    printf("%d ", node->val);
}

BST_status BST_print_pos(const BST *bst) {
    if (!bst)
        return BST_ERR_WRONG_PTR;

    _print_bstnode_pos(bst->root);
    return BST_OK;
}

BST_status BST_remove(BST *bst);
