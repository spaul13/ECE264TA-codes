CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wunreachable-code -Wvla -Werror
COVFLAGS = -fprofile-arcs -ftest-coverage
GCC = gcc $(CFLAGS) 
OBJS = pa15.o huffman.o  

pa15: $(OBJS)
	$(GCC) $(OBJS) -o $@

pa15.o: pa15.c 
	$(GCC) -c $< -o $@

huffman.o: huffman.c
	$(GCC) -c $< -o $@

clean:
	rm -f *.o
	rm -f pa15
