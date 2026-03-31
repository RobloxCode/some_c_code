#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H
#include <stddef.h>

typedef enum {
    BST_OK                  = 0,
    BST_ERR_WRONG_PTR       = 1,
    BST_ERR_INIT_NODE       = 2,
    BST_ERR_REPEATED_VAL    = 3,
    BST_ERR_EMPTY_TREE      = 4,
    BST_ERR_VAL_NOT_FOUND   = 5,
} BST_status;

typedef struct BSTNode {
    int val;
    struct BSTNode *left_child;
    struct BSTNode *right_child;
} BSTNode;

typedef struct {
    BSTNode *root;
    size_t height;
} BST;

/**
 * Initializes the binary search tree
 */
BST *BST_init(void);

/**
 * Destroys the binary search tree
 * @param bst a double pointer to the BST struct
 */
BST_status BST_deinit(BST **bst);

/**
 * Adds a new node to the tree, it will find where to add it to
 * @param bst a pointer to a BST struct
 * @param val value to be added
 */
BST_status BST_append(BST *bst, const int val);

/**
 * Not implemented yet
 */
BST_status BST_remove(BST *bst, int val);

/*
 * Prints to the console the tree values in preorder
 * Node -> left -> right
 * @param bst a pointer to a BST struct
 */
BST_status BST_println_pre(const BST *bst);

/*
 * Prints to the console the tree values in inorder
 * left -> Node -> right
 * @param bst a pointer to a BST struct
 */
BST_status BST_println_ino(const BST *bst);

/*
 * Prints to the console the tree values in postorder
 * left -> right -> Node
 * @param bst a pointer to a BST struct
 */
BST_status BST_println_pos(const BST *bst);

BST_status BST_get_min(const BST *bst, int *out);

#endif
