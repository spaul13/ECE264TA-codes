GCC = gcc -g
OBJFILES = tree.o scanner.o expressionTree.o

all: pa12 
	
pa12: pa12.o $(OBJFILES)
	$(GCC) -o pa12 pa12.o $(OBJFILES)
	
%o : %c
	$(GCC) -c $<
	
clean:
	rm -f *.o
	rm -f scannertest
	rm -f pa12
