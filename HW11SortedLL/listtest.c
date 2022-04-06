#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

int main(int argc, char ** argv) {
	
	PathLL * list = buildPaths();
	
	addNode(list, "ness");
	addNode(list, "nese");
	
	printPaths(list, stdout);
	
	printf("\n");
		
	printPaths(list, stdout);
	
	return EXIT_SUCCESS;
}