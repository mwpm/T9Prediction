/*
Michael Molina
3/3/2014
CSE 374 Homework 5
trie.c file for t9prediction program split into two 
source files (main.c and trie.c)
includes struct functions to create tree and read from it
with some other helpful functions.
*/

#include "header.h"

//Takes the root of the tree, a word pointer and its actual length
//and adds it to the tree returning the updated tree
 tNode* addWord(tNode *root, char *word, int length) {
	struct tNode* current; //travers through tree without changing it
	int i;
	if (root == NULL) {
		root = newNode();
	}
	current = root;
	//Makes nodes to respective key equivlent and stores data in last node
	for(i =0; i < length; i++) {
		int num;
		num = letterToNumber(word[i]);
		if(current) {
			if(!current->next[num]) {
				//want to add new node
				struct tNode* child = newNode();
				current->next[num] = child;
			}
		}
		current = current->next[num];
	}
	//Checks for '#' entries and creates a new node if found
	while(current && current->data) {
		if(!current->next[POUND]) {
			struct tNode* hashTagNode = newNode();
			current->next[POUND] = hashTagNode;
		}
		current = current->next[POUND];
	}
	if(current != NULL) {
		current->data = word;
	}
	return root;

}

//Takes a node of a tree and frees the allocated memory of 
//that node and all of its children
void freeNode(struct tNode * node) {
	if (node) {
		int i;
		for (i=0; i<NUMKEYS; i++) {
			if(node->next[i]) {
				freeNode(node->next[i]);
				node->next[i] = NULL;
			}
		}
		if(node->data) {
			free(node->data);
			node->data = NULL;
		}
		free(node);
	}
}

//Returns a new empty node
struct tNode* newNode() {
	struct tNode* newNode = (struct tNode*)malloc(sizeof(struct tNode));
	newNode->data=NULL;
	int i;
	for(i=0;i<NUMKEYS;i++) {
		newNode->next[i] = NULL;
	}
	return newNode;
}

//Takes the root of the tree and a dictionary txt file
//and returns a tree with all of the words inside of it
struct tNode* getDictionary(tNode* root, char* dict) {
	FILE* fp; //given dictionary txt file
	char line[MAXWORDLENGTH]="";
	fp = fopen(dict, "r");
		if(fp==NULL) {
		fprintf(stderr, FILENOTFOUND);
		exit(EXIT_FAILURE);
	}
	while(fgets(line, MAXWORDLENGTH, fp) != NULL) {
		int lastChar = strlen(line) - 1; //excludes the \n character
		if(line[lastChar] == '\n') {
			line[lastChar] = '\0'; //replaces \n with \0
		}
		int length = strlen(line); //actual length
		char* pline = (char*)malloc(sizeof(line)); //malloc for word data
			int i;
			//update malloc string at unique address
			for(i=0; i< strlen(line); i++) {
				pline[i] = line[i];
			}
			root = addWord(root, pline, length);
		}
	fclose(fp);
	return root;
}

//Takes the root of a tree and a string of numbers
//and returns the node with the word in its data field
//and a message if its not.
struct tNode* readWord(tNode *root, char *number) {
	 struct tNode * current = root; //traverse tree without changing it
	 int length = strlen(number);
	 int i = 0;

	 char lastChar; //last charcter to see if its a '#'

	 if (current && number) {
		 while (current->next[charNumToNum(number[i])] && i < length) {
			 current = current->next[charNumToNum(number[i])];
			 lastChar = number[i];
			 i++;
		 }
		 if (i != length || (current->data == NULL)) {// current->next is null
			 lastChar = number[length-1];
			 if (lastChar == '#') {
				 fprintf(stdout, NOT9ONYMS);
			 } else if (lastChar >= '2' && lastChar <= '9') {
				 fprintf(stdout, NOTINDICT);
			 } else {
				fprintf(stdout, INCORRECTKEY);
			 }
			 return current->next[charNumToNum(number[i])];
		 } 
	 }
	 return current;

}