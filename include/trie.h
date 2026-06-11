#ifndef TRIE_H
#define TRIE_H

typedef struct TrieNode {
  char c;
  int children_len;
  struct TrieNode **children;
  unsigned short isend;
} TrieNode;

TrieNode* trie_header_init();

#endif
