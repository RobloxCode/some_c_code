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
    free(node);
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
            free(new);
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

    return BST_OK;
}

static void _print_bstnode_pre(const BSTNode *node) {
    if (!node)
        return;

    printf("%d ", node->val);
    _print_bstnode_pre(node->left_child);
    _print_bstnode_pre(node->right_child);
}

BST_status BST_println_pre(const BST *bst) {
    if (!bst)
        return BST_ERR_WRONG_PTR;

    _print_bstnode_pre(bst->root);
    printf("\n");
    return BST_OK;
}

static void _print_bstnode_ino(const BSTNode *node) {
    if (!node)
        return;

    _print_bstnode_ino(node->left_child);
    printf("%d ", node->val);
    _print_bstnode_ino(node->right_child);
}

BST_status BST_println_ino(const BST *bst) {
    if (!bst)
        return BST_ERR_WRONG_PTR;

    _print_bstnode_ino(bst->root);
    printf("\n");
    return BST_OK;
}

static void _print_bstnode_pos(const BSTNode *node) {
    if (!node)
        return;

    _print_bstnode_pos(node->left_child);
    _print_bstnode_pos(node->right_child);
    printf("%d ", node->val);
}

BST_status BST_println_pos(const BST *bst) {
    if (!bst)
        return BST_ERR_WRONG_PTR;

    _print_bstnode_pos(bst->root);
    printf("\n");
    return BST_OK;
}

static void _swap_node_vals(BSTNode *node1, BSTNode *node2) {
    int tmp = node1->val;
    node1->val = node2->val;
    node2->val = tmp;
}

static BST_status _init_left_max_ptr(
    BSTNode *to_del,
    BSTNode **left_max,
    BSTNode **parent
) {
    *left_max = to_del->left_child;
    *parent = to_del;
    while ((*left_max)->right_child) {
        *parent = *left_max;
        *left_max = (*left_max)->right_child;
    }

    return BST_OK;
}

static BST_status _init_del_ptrs(
    const BST *bst,
    const int val,
    BSTNode **to_del,
    BSTNode **parent
) {
    if (!bst || !bst->root)
        return BST_ERR_WRONG_PTR;

    *parent = NULL;

    BSTNode *cur = bst->root;
    while (1) {
        if (cur->val == val) {
            *to_del = cur;
            return BST_OK;
        } else if (cur->val < val) {
            if (!cur->right_child)
                return BST_ERR_VAL_NOT_FOUND;

            *parent = cur;
            cur = cur->right_child;
        } else {
            if (!cur->left_child)
                return BST_ERR_VAL_NOT_FOUND;

            *parent = cur;
            cur = cur->left_child;
        }
    }
}

static void _replace_child(
    BST *bst,
    BSTNode *parent,
    BSTNode *old,
    BSTNode *new_child
) {
    if (parent) {
        if (parent->left_child == old)
            parent->left_child = new_child;
        else
            parent->right_child = new_child;
    } else {
        bst->root = new_child;
    }
}

BST_status BST_remove(BST *bst, int val) {
    if (!bst)
        return BST_ERR_WRONG_PTR;

    if (!bst->root)
        return BST_ERR_EMPTY_TREE;

    BST_status status = BST_OK;
    BSTNode *to_del = NULL;
    BSTNode *parent = NULL;
    BSTNode *left_max = NULL;

    if ((status = _init_del_ptrs(bst, val, &to_del, &parent)) != BST_OK)
        return status;

    if (!to_del->left_child && !to_del->right_child) {
        _replace_child(bst, parent, to_del, NULL);

        goto free_node;
    } else if (!to_del->left_child) {
        BSTNode *new_child = to_del->right_child;

        _replace_child(bst, parent, to_del, new_child);

        goto free_node;
    } else if (!to_del->right_child) {
        BSTNode *new_child = to_del->left_child;

        _replace_child(bst, parent, to_del, new_child);

        goto free_node;
    } else {
        if ((status = _init_left_max_ptr(to_del, &left_max, &parent)) != BST_OK)
            return status;

        _swap_node_vals(to_del, left_max);
        BSTNode *new_child = left_max->left_child;

        if (parent->right_child == left_max)
            parent->right_child = new_child;
        else
            parent->left_child = new_child;

        free(left_max);
        return BST_OK;
    }

free_node:
    free(to_del);
    return BST_OK;
}

BST_status BST_get_min(const BST *bst, int *out) {
    if (!bst || !out)
        return BST_ERR_WRONG_PTR;

    if (!bst->root)
        return BST_ERR_EMPTY_TREE;

    BSTNode *cur = bst->root;
    *out = cur->val;
    cur = cur->left_child;
    *out = cur->val;
    while (cur) {
        *out = cur->val;
        cur = cur->right_child;
    }

    return BST_OK;
}
