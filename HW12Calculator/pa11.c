#include <stdio.h>
#include <stdlib.h>
#include "calc.h"

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf(stderr, "Incorrect number of arguments.\n");
		fprintf(stderr, "Usage: ./pa11 <input file>\n");		
		return EXIT_FAILURE;
	}
	
	FILE * fin = fopen(argv[1], "r");
	if (fin == NULL) {
		fprintf(stderr, "Error opening file\n");
		return EXIT_FAILURE;
	}
	
	Stack * s = calculate(fin);
	
	fclose(fin);
	
	if (s->size != 1) {
		fprintf(stderr, "Some error calculating\n");
		return EXIT_FAILURE;
	}
	
	valtype f = pop(s);
	printf("%f\n", f);
	
	freeStack(s);
	
	return EXIT_SUCCESS;
}
