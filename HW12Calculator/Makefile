GCC = gcc -g
OBJFILES = stack.o calc.o
PA10MAIN = pa11.o

all: pa11
	

pa11: $(OBJFILES) $(PA10MAIN)
	$(GCC) $(OBJFILES) $(PA10MAIN) -o pa11

%o: %c
	$(GCC) -c $<

clean:
	rm -f pa11
	rm -f *.o