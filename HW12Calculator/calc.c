#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

bool isOp(char * buf) {
	if (strlen(buf) != 1) return false;
	char o = buf[0];
	return ((o == ADD) ||
	        (o == SUB) ||
	        (o == MUL) ||
					(o == DIV));
}

valtype calcHelper(Stack * s, char op) {
  if (isEmpty(s)) {
    fprintf(stderr, "Error: calculating over empty stack\n");
  }
 	valtype op1 = pop(s);
 	valtype op2 = pop(s);
	valtype result;
 	switch(op) {
 		case ADD:
		result = op2 + op1;
 		break;
 		case SUB:
		result = op2 - op1;
 		break;            
 		case MUL:         
		result = op2 * op1;
 		break;            
 		case DIV:         
		result = op2 / op1;
 		break;
  }

	fprintf(stderr, "Computing %f %c %f -> %f\n", op2, op, op1, result);

	return result;
}

Stack * calculate(FILE * fin) {
	
	Stack * s = allocStack();
	
	char buf[256];
	
	while (fscanf(fin, "%s", buf) == 1) {
		// fprintf(stderr, "Read: %s\n", buf);
		if (isOp(buf)) {
			push (s, calcHelper(s, buf[0]));
		} else {
			push(s, atof(buf));
		}
	}	
	
	if (s->size != 1) {
		fprintf(stderr, "Malformed input!\n");
		exit(1);
	}
	
	return s;
}
