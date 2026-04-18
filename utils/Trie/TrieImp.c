#include "TrieImp.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    LEFT,
    RIGHT
} direction;

TrieNode *TrieNode_init(char val)
{
    TrieNode *new_node = malloc(sizeof *new_node);
    if (!new_node)
        return NULL;

    new_node->val = val;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

Trie *Trie_init()
{
    Trie *new_trie = malloc(sizeof *new_trie);
    if (!new_trie)
        return NULL;

    new_trie->root = NULL;
    return new_trie;
}

static char _get_min_char(char c1, char c2)
{
    return c1 < c2 ? c1 : c2;
}

static TrieNode *_push_helper(TrieNode *node, char val)
{
    if (node) {
        TrieNode *new_node = malloc(sizeof *new_node);
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->val = val;
        return new_node;
    }

    if (node->val < val) {
        node->left = _push_helper(node->left, val);
    } else {
        node->right = _push_helper(node->right, val);
    }

    return node;
}

int Trie_push(Trie *trie, char val)
{
    if (!trie)
        return 1;

    trie->root = _push_helper(trie->root, val);

    return 0;
}
int Trie_remove(Trie *trie);
int Trie_deinit(Trie **trie);
