/* tnine is a program that drives a trie / t9 program.  This code
   will build a trie, according to trienode.  It will also run
   an interactive session where the user can retrieve words using
   t9 sequences.
   CSE374, HW5, 22wi 
   Xiaoyu Zhou
   2022/3/2
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trienode.h"

// run_session run the on-going decoding interaction with the
// user.  It requires a previously build wordTrie to work.
void run_session(trieNode *wordTrie) {
  printf("Enter \"exit\" to quit.\n");
  char inputIndex[MAXLEN];
  int loop = 1;
  trieNode * current = wordTrie;
  while (loop) {
    printf("Enter Key Sequence (or \"#\" for next word): \n");
    scanf("%s", inputIndex);
    if (strncmp("exit", inputIndex, strlen("exit")) == 0) {
      loop = 0;
    } else {
      if (inputIndex[0] != '#') {
        current = getNode(wordTrie, inputIndex);
      } else {
        current = getNode(current, inputIndex);
      }
      if (current == NULL) {
        if (inputIndex[strlen(inputIndex) - 1] == '#') {
          printf("There are no more T9onyms\n");
        } else {
          printf("Not found in current dictionary.\n");
        }
      } else {
        if (current -> word) {
          printf("\'%s\'\n", current -> word);
        } else {
          printf("Not found in current dictionary.\n");
        }
      }
    }
  }
}

int main(int argc, char **argv) {
  FILE *dictionary = NULL;
  trieNode *wordTrie = NULL;
  trieNode* root = SetNullNode();

  if (argc < 2) {
    fprintf(stderr, "Usage: %s [DICTIONARY]\n", argv[0]);
    return EXIT_FAILURE;
  } else {
    dictionary = fopen(argv[1], "r");
    if (!dictionary) {
      fprintf(stderr, "Error: Cannot open %s\n", argv[1]);
      return EXIT_FAILURE;
    }
  }

  // build the trie
  build_tree(root, dictionary);

  // run interactive session
  run_session(root);

  // clean up
  free_tree(root);
  fclose(dictionary);
  return(EXIT_SUCCESS);
}





