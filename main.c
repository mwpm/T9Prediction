/*
Michael Molina
3/3/2014
CSE 374 Homework 5
main.c file for t9prediction program split into two 
source files (main.c and trie.c)
includes user interface and simple functions.
*/

#include "header.h"
#include "trie.c"

int main(int argc, char** argv) {
	char number[MAXWORDLENGTH];
	char* ans;
	tNode* root = NULL; //intiate root 
	root = getDictionary(root, argv[1]); //make tree with dictionary
	tNode* result = root; //tracks previous result if '#' is inputted by user
	printf("%s\n", "Enter \"exit\" to quit.");
	//User interface keeps going until user types "exit"
	while(strncmp(&number[0], "exit", MAXWORDLENGTH) != 0 ) {
		printf("%s\n", "Enter Key Sequence (or \"#\" for next word):");
		printf("%s", "> " );
		scanf("%s", &number[0]); //takes a user input string
		//check if string starts with # to start reading tree from root or previous result
		if(number[0] == '#') {
			result = readWord(result, number);
		} else if(strncmp(&number[0], "exit", MAXWORDLENGTH) != 0){
			result = readWord(root, number);
		}
		//safety check to make sure there is a result node
		if(result && strncmp(&number[0], "exit", MAXWORDLENGTH) != 0) {
			if(result->data) {
				ans = result->data;
				printf("\t'%s'\n", ans);
			}
		}
	}
	free(result);
	result = NULL;
	freeNode(root);
	root = NULL;
	return 0;
}

//Passes a single character into function 
//and converts and returns the number corresponding 
//a number keypad EX: 2 -> a | b | c 
int letterToNumber(char c) {
	if(c >=97 && c <= 99) {
		return TWO; //2 keypad
	} else if(c >99 && c <=102) {
		return THREE; //3 keypad
	} else if (c >102 && c <=105) {
		return FOUR; //4 keypad
	} else if (c >105 && c <=108) {
		return FIVE; //5 keypad
	} else if (c >108 && c <=111) {
		return SIX; //6 keypad
	} else if (c >111 && c <=115) {
		return SEVEN; //7 keypad
	} else if (c >115 && c <=118) {
		return EIGHT; //8 keypad
	} else if (c >118 && c <=122) {
		return NINE; //9 keypad
	}else if (c == ASCII_POUND) {
		return POUND; //# keypad
	}
	return -1; //nothing
}

//Passes a single number character into function
//and converts and returns the actual integer
int charNumToNum(char c) {
	if (c>=50 && c<=57) {
		return c - '0' - 2;
	} else if (c == ASCII_POUND) {
		return POUND; // # numpad
	} else {
		return -1;
	}
}

