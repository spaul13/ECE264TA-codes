#include "scanner.h"

int main (int argc, char ** argv) {
	scannerInit(argv[1]);
	
	Token t;
	do {
		t = nextToken();
		printToken(t, stdout);
	} while (t.type != T_EOF);
	
	scannerClose();
}