#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

Stack * allocStack() {
	Stack * ret = malloc(sizeof(Stack));
	ret->size = 0;
	ret->head = NULL;
	return ret;
}

void freeStack(Stack * s) {
	if (!isEmpty(s) != 0) {
		fprintf(stderr, "trying to free non-empty stack.\n");
		while (!isEmpty(s)) pop(s);
	}
	free(s);
}

void push(Stack * s, valtype f) {
	Node * n = malloc(sizeof(Node));
	n->next = s->head;
	n->val = f;
	s->head = n;
	s->size++;
}

valtype pop(Stack * s) { //Return SENTINEL value type if empty
	valtype f = peek(s);
	Node * tmp = s->head;
	s->head = s->head->next;
	s->size--;
	free(tmp);
	return f;
}

valtype peek(Stack * s) {
	if (isEmpty(s)) {
		fprintf(stderr, "trying to peek from an empty stack\n");
		exit(1);
	}
	return s->head->val;
}

bool isEmpty(Stack * s) {
	return s->size == 0;
}

void printStack(Stack * s, FILE * fptr) {
	Node * cur = s->head;
	while (cur != NULL) {
		fprintf(fptr, "%f\n", cur->val);
		cur = cur->next;
	}
}