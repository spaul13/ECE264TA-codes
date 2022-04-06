CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
TESTS = -DTEST_READ -DTEST_WRITE -DTEST_SORTID -DTEST_SORTFIRSTNAME -DTEST_SORTLASTNAME
GCC = gcc $(CFLAGS) $(TESTS)
OBJS =  maze.o path.o pa10.o solver.o mazehelper.o list.o
VALGRIND = valgrind --tool=memcheck --leak-check=yes --verbose

# This Makefile can be shortened by using loop. 
# It shows all steps to explain what it does

# test integrate1 using five different functions
# each function is tested using three sets of input data
all: pa10
	

pa10: $(OBJS)
	$(GCC) $(OBJS) -o pa10

test: pa10
	./pa10 inputs/maze6 path_out

%.o: %.c 
	$(GCC) -c $<

clean:
	/bin/rm -f *.o
	/bin/rm -f pa10
	/bin/rm -f path_out
