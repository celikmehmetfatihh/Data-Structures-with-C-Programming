//Hocam I made two projects, but I submitted like how Meryem hoca said. So, you need to add #include stackStatic.c probably. The code works without error, tested.

#include <stdio.h>
#include <string.h>
#include "stackDynamic.h"

#define MAXSIZE 50

struct Node{
	char c;
	struct Node *next;
};
typedef struct Node StackRecord;
typedef StackRecord *Stack;


int main(){
	Stack firstHalf;
	char phrase[MAXSIZE];
	 
    printf("Please enter a phrase to find out if it is palindrome or not!\n");
 	gets(phrase);
 	firstHalf = CreateStack();
	IsPalindrome(phrase, firstHalf);
 		
	return 0;
}
