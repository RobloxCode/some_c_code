#ifndef TRIEIMP_H
#define TRIEIMP_H

typedef struct TrieNode {
    char val;
    struct TrieNode *left;
    struct TrieNode *right;
} TrieNode;

typedef struct {
    TrieNode *root;
} Trie;

Trie *Trie_init();
int Trie_push(Trie *trie, char val);
int Trie_remove(Trie *trie);
int Trie_deinit(Trie **trie);

#endif
