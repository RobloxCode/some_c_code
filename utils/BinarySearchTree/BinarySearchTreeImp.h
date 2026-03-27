#ifndef BST_H
#define BST_H
#include <stddef.h>

typedef enum {
    BST_OK                  = 0,
    BST_ERR_WRONG_PTR       = 1,
    BST_ERR_INIT_NODE       = 2,
    BST_ERR_REPEATED_VAL    = 3,
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
 * Initialices a new node
 * @param val value that the new node will contain
 */
BSTNode *BSTNode_init(const int val);

/**
 * Destroys the node
 * @param bstnode a double pointer to the BSTNode struct
 *                since the current pointer to the
 *                node will be set to NULL
 */
void BSTNode_deinit(BSTNode **bstnode);

/**
 * Initialices the binary search tree
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
BST_status BST_remove(BST *bst);

/*
 * Prints to the console the tree values in preorder
 * Node -> left -> right
 * @param bst a pointer to a BST struct
 */
BST_status BST_print_pre(const BST *bst);

/*
 * Prints to the console the tree values in inorder
 * left -> Node -> right
 * @param bst a pointer to a BST struct
 */
BST_status BST_print_ino(const BST *bst);

/*
 * Prints to the console the tree values in postorder
 * left -> right -> Node
 * @param bst a pointer to a BST struct
 */
BST_status BST_print_pos(const BST *bst);

#endif
