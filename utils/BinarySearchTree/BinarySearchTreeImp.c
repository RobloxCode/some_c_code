#include "BinarySearchTreeImp.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static BSTNode *BSTNode_init(const int val) {
    BSTNode *bstnode = malloc(sizeof *bstnode);
    if (!bstnode)
        return NULL;

    bstnode->val = val;
    bstnode->left_child = NULL;
    bstnode->right_child = NULL;
    return bstnode;
}

static void BSTNode_deinit(BSTNode **bstnode) {
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

static BST_status _init_to_del_ptrs(
    const BST *bst,
    const int val,
    BSTNode **to_del,
    BSTNode **before
) {
    if (!bst || !bst->root)
        return BST_ERR_WRONG_PTR;

    *before = NULL;

    BSTNode *cur = bst->root;
    while (1) {
        if (cur->val == val) {
            *to_del = cur;
            return BST_OK;
        } else if (cur->val < val) {
            if (!cur->right_child)
                return BST_ERR_VAL_NOT_FOUND;

            *before = cur;
            cur = cur->right_child;
        } else {
            if (!cur->left_child)
                return BST_ERR_VAL_NOT_FOUND;

            *before = cur;
            cur = cur->left_child;
        }
    }
}

void _get_max_left(BSTNode *node) {
    if (!node)
        return;
}

BST_status BST_remove(BST *bst, int val) {
    if (!bst)
        return BST_ERR_WRONG_PTR;

    if (!bst->root)
        return BST_ERR_EMPTY_TREE;

    BST_status status = BST_OK;
    BSTNode *to_del = NULL;
    BSTNode *before = NULL;

    if ((status = _init_to_del_ptrs(bst, val, &to_del, &before)) != BST_OK) {
        return status;
    }

    // if (!to_del->left_child && !to_del->right_child) {
    //     BSTNode_deinit(&to_del);
    //     return BST_OK;
    // } else if (to_del->left_child && !to_del->right_child) {
    //     before = to_del->left_child;
    //     BSTNode_deinit(&to_del);
    // } else if (!to_del->left_child && to_del->right_child) {
    //     before = to_del->right_child;
    //     BSTNode_deinit(&to_del);
    // } else {
    //     _get_max_left(to_del);
    // }
    //
    return BST_OK;
}
