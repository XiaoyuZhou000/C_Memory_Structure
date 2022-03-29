/* trie implements a trie, made of trieNodes. This includes
   code to build, search, and delete a trie
   CSE374, HW5, 22wi 
   Xiaoyu Zhou
   2022/3/2
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trienode.h"

/* You'll want to prototype any helper functions you need here */

// Create a new node and set all value in the node to NULL
trieNode * SetNullNode();

// Get the corresponding number index of the given character
int getNum(char letter);

// given a pattern, return the node stored in the
// appropriate trieNode
trieNode* getNode(trieNode* root, char* pattern);


/* You'll need to implement the functions declare in trienode.h */
/* As well as the helpfer functions you prototype above. */
int getNum(char letter) {
  char numList[26] = {1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4,
                      5, 5, 5, 6, 6, 6, 6, 7, 7, 7, 8, 8, 8, 8};
  return numList[letter - 'a'];
}

trieNode* SetNullNode() {
  trieNode* newNode = (trieNode*) malloc(sizeof(struct trieNode));
  newNode -> word = NULL;
  for (int i = 0; i < BRANCHES; i++) {
    newNode -> branches[i] = NULL;
  }
  return newNode;
}

// given a word list (dict), build a trie that holds
// each word.  Return pointer to the root node.
void build_tree(trieNode * root, FILE * dictionary) {
  if (dictionary != NULL) {
    char dictline[MAXLEN];
    while (fgets(dictline, MAXLEN, dictionary) != NULL) {
      trieNode * current = root;
      char * wordtext = (char *) malloc(strlen(dictline));
      if (wordtext != NULL) {
        strncpy(wordtext, dictline, strlen(dictline) - 1);
        wordtext[strlen(dictline) - 1] = '\0';
      }
      int i = 0;
      // Trace to the last node of the word
      while (dictline[i] != '\n') {
        int num = getNum(dictline[i]);
        if (current -> branches[num] == NULL) {
          current -> branches[num] = SetNullNode();
        }
        current = current -> branches[num];
        i++;
      }
      // Prepare for "#" option
      while (current -> branches[0] != NULL) {
        current = current -> branches[0];
      }
      // Store value in node
      if (current -> word == NULL) {
        current -> word = wordtext;
      } else {
        current -> branches[0] = SetNullNode();
        current = current -> branches[0];
        current -> word = wordtext;
      }
    }
  } else {
    fprintf(stderr, "Not found in current dictionary.\n");
  }
}

char* get_word(trieNode *root, char *pattern) {
  char* word = (char*)malloc(strlen(pattern) + 1);
  if (pattern != NULL) {
    strncpy(word, pattern, strlen(pattern));
  }
  trieNode* current = root;
  for (int i = 0; i < strlen(pattern); i++) {
    if (pattern[i] != '#') {
      if (current -> branches[getNum(pattern[i])] == NULL) {
        return "Not found in current dictionary.\n";
      }
      strncat(word, current -> word, 1);
      current = current -> branches[getNum(pattern[i])];
    } else {
      if (current -> branches[1] == NULL) {
        return "There are no more T9onyms\n";
      }
      strncat(word, current -> word, 1);
      current = current -> branches[0];
    }
  }
  return word;
}


trieNode * getNode(trieNode * root, char * pattern) {
  trieNode * current = root;
  for (int i = 0; i < strlen(pattern); i++) {
    if (pattern[i] != '#') {
      if (current -> branches[(pattern[i] - '0')] == NULL) {
        return NULL;
      }
      current = current -> branches[(pattern[i] - '0')];
    } else {
      if (current -> branches[0] == NULL) {
        return NULL;
      }
      current = current -> branches[0];
    }
  }
  return current;
}

void free_tree(trieNode * root) {
  for (int i = 0; i < BRANCHES; i++) {
    if (root -> branches[i] != NULL) {
      free_tree(root -> branches[i]);
      free(root -> branches[i]);
    }
  }
  if (root -> word != NULL) {
    free(root -> word);
  }
  if (root != NULL) {
    free(root);
  }
}
