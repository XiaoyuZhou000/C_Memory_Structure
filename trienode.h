 /* trienode.h contains structure and function declarations for 
   a trie implementation 
   CSE374, HW5, 22Wi 
   Xiaoyu Zhou
   2022/3/2
*/

#ifndef TRIENODE_H
#define TRIENODE_H

#include <stdio.h>

#define MAXLEN 50
#define BRANCHES 9

// trieNode is one node in an 9-tree, where branches correspond to
// # and the T9 alphabet.
typedef struct trieNode {
  struct trieNode *branches[BRANCHES];
  char *word;
} trieNode;

// given a word list (dict), build a trie that holds
// each word.  Return pointer to the root node.
void build_tree(trieNode* root, FILE *dictline);

// given a pattern, return the word stored in the
// appropriate trieNode
char* get_word(trieNode *root, char *pattern);

// deletes the entire tree branching from root
void free_tree(trieNode *root);

// Create a new node and set all value in the node to NULL
trieNode * SetNullNode();

// Get the corresponding number index of the given character
int getNum(char letter);

// given a pattern, return the node stored in the
// appropriate trieNode
trieNode* getNode(trieNode* root, char* pattern);


#endif
