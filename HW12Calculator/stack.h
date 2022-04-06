#ifndef _STACK_H
#define _STACK_H

#include <stdbool.h>

typedef float valtype;

typedef enum Operations {
	ADD = '+',
	SUB = '-',
	MUL = '*',
	DIV = '/'
} Operations;

typedef struct Node {
	valtype val;
	struct Node * next;
} Node;

typedef struct Stack {
	Node * head;
	int size;
} Stack;

Stack * allocStack();

void freeStack(Stack * s);

void push(Stack * s, valtype f);

valtype pop(Stack * s); //Return SENTINEL value type if empty

valtype peek(Stack * s); //Return SENTINEL value type if empty

bool isEmpty(Stack * s);

void printStack(Stack * s, FILE * fptr); //Print contents of stack without popping

#endif