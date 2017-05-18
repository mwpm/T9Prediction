t9Prediction : main.o trie.o
	gcc -o t9Prediction main.o

main.o : main.c header.h trie.o
	gcc -c -o main.o main.c

trie.o : trie.c header.h 
	gcc -c -o trie.o trie.c