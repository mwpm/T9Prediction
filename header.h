/*
Michael Molina
3/3/2014 
CSE 374 Homework 5
header file for t9prediction program split into two 
source files (main.c and trie.c)
includes C libraries and define global constants 
and tree node. Also initiates all the functions.
*/

#ifndef HEADER_H_
#define HEADER_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ASCII 48
#define NUMPAD 2
#define TWO 0
#define THREE 1
#define FOUR 2
#define FIVE 3
#define SIX 4
#define SEVEN 5
#define EIGHT 6
#define NINE 7
#define POUND 8
#define ASCII_POUND 35
#define NUMKEYS 9
#define MAXWORDLENGTH 20
#define FILENOTFOUND "File does not exist"
#define NOT9ONYMS "\tThere are no more T9onyms\n"
#define NOTINDICT "\tNot found in current dictionary\n"
#define INCORRECTKEY "\tIncorrect Key input\n"

typedef char treeElement;

//a single t9 node pointing to a data storing a word and 9 other tNodes
typedef struct tNode{
	treeElement* data; //holds word
	struct tNode* next[NUMKEYS]; //holds 8 nodes 
} tNode;

int letterToNumber(char c);
tNode* addWord(tNode *root, char *word, int length);
struct tNode* readWord(tNode *root, char *number);
int charNumToNum(char c);
struct tNode* newNode();
struct tNode* getDictionary(tNode* root, char* dict);

#endif /*HEADER_H_*/