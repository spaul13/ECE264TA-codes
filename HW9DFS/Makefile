CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
TESTS = -DTEST_READ -DTEST_WRITE -DTEST_SORTID -DTEST_SORTFIRSTNAME -DTEST_SORTLASTNAME
GCC = gcc $(CFLAGS) $(TESTS)
OBJS =  maze.o path.o pa08.o solver.o mazehelper.o
VALGRIND = valgrind --tool=memcheck --leak-check=yes --verbose

# This Makefile can be shortened by using loop. 
# It shows all steps to explain what it does

# test integrate1 using five different functions
# each function is tested using three sets of input data
all: pa08
	

pa08: $(OBJS) path.h maze.h
	$(GCC) $(OBJS) -o pa08

test: pa08
	./pa08 inputs/maze1 path_out

%.o: %.c 
	$(GCC) -c $<

clean:
	/bin/rm -f *.o
	/bin/rm -f pa08