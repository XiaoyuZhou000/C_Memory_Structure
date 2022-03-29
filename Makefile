# Xiaoyu Zhou
# 2022/3/2
all: t9

# executable
t9: tnine.o trie.o
	gcc -Wall -std=c11 -g -o t9 tnine.o trie.o

tnine.o: tnine.c trienode.h
	gcc -Wall -std=c11 -g -c tnine.c

trie.o: trie.c trienode.h
	gcc -Wall -std=c11 -g -c trie.c

clean:
	rm -f *.o t9 *~

