#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "tree.h"

static bool isRParen(Token t) {
	return (t.type == T_RPAREN);
}

static bool isOp(Token t) {
	return ((t.type == T_ADD) ||
	    (t.type == T_SUB) ||
	    (t.type == T_DIV) ||
			(t.type == T_MUL));
}

TreeNode * buildETHelper(Scanner * s) {
	Token t = nextToken(s);
	
	TreeNode * retval;
	
	switch(t.type) {
	case T_VAL:
	{
		retval = buildTreeNode(t); 
		break;
	}
	case T_LPAREN:
	{
		TreeNode * leftExp = buildETHelper(s);
		Token op = nextToken(s);
		if (!isOp(op)) {
			fprintf(stderr, "Parse error, expecting op, got: ");
			printToken(op, stderr);
			exit(1);
		}
		TreeNode * rightExp = buildETHelper(s);
		Token rp = nextToken(s);
		if (!isRParen(rp)) {
			fprintf(stderr, "Parse error, expecting ), got: ");
			printToken(rp, stderr);
			exit(1);
		}
		retval = buildTreeNode(op);
		retval->left = leftExp;
		retval->right = rightExp;
		break;
	}
	default:
	{
		fprintf(stderr, "Parse error: expecting val or (, got: ");
		printToken(t, stderr);
		exit(1);
	}
	}
	
	return retval;
}

TreeNode * buildExpressionTree(Scanner * s) {
	if (s->buf == NULL) {
		fprintf(stderr, "Scanner uninitialized!");
		exit(1);
	}
	
	TreeNode * retval = buildETHelper(s);
	Token t = nextToken(s);
	if (t.type != T_EOF) {
		fprintf(stderr, "Parse error: should have reached end of file, got: ");
		printToken(t, stderr);
	}
	
	return retval;
}

void makePostFix(TreeNode * t, FILE * fptr) {
	
	char * retval;
	if (t->t.type == T_VAL) {
		fprintf(fptr, "%f ", t->t.value);
		return;
	}
	
	makePostFix(t->left, fptr);
	makePostFix(t->right, fptr);
	
	fprintf(fptr, "%c ", t->t.type);
		
	return;
}