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

BSTNode *BSTNode_init(const int val);
void BSTNode_deinit(BSTNode **bstnode);

BST *BST_init(void);
BST_status BST_deinit(BST **bst);
BST_status BST_append(BST *bst, const int val);
BST_status BST_remove(BST *bst);

BST_status BST_print_pre(const BST *bst);
BST_status BST_print_ino(const BST *bst);
BST_status BST_print_pos(const BST *bst);

#endif
