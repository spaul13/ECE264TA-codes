CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
TESTFALGS = -DTEST_INTEGRATE -DRUN_INTEGRATE
LIBS = -lm
GCC = gcc $(CFLAGS) $(TESTFALGS)
EXEC = hw3

FUNCS = func1.o func2.o func3.o func4.o func5.o
OBJS =  hw3.o answer3.o $(FUNCS)

# This Makefile can be shortened by using loop. 
# It shows all steps to explain what it does

# test integrate1 using five different functions
# each function is tested using three sets of input data
$(EXEC): $(OBJS) 
	$(GCC) $(OBJS) -o $(EXEC) $(LIBS)

testall: $(EXEC)
	./$(EXEC) testcases/test1 testcases/output1
	./$(EXEC) testcases/test2 testcases/output2
	./$(EXEC) testcases/test3 testcases/output3
	./$(EXEC) testcases/test4 testcases/output4
	./$(EXEC) testcases/test5 testcases/output5


testgen: testgen.o answer3.o $(FUNCS) 
	$(GCC) testgen.o answer3.o $(FUNCS) -o testgen $(LIBS)

testcases: testgen hw3.h
	/bin/rm -f -r testcases
	mkdir testcases
	./testgen testcases/test1 -5.0 10.5 100000
	./testgen testcases/test2 -1.0 23.0 100000
	./testgen testcases/test3 5.8 37.9 100000
	./testgen testcases/test4 8.0 102.5 100000
	./testgen testcases/test5 -7.2 91.8 100000

.c.o: 
	$(GCC) -c $*.c 

clean:
	/bin/rm -f input*
	/bin/rm -f *.o
	/bin/rm -f testgen 
	/bin/rm -f *.gcda *.gcno gmon.out *gcov
	/bin/rm -f hw3 hw3.prof
	/bin/rm -f -r testdir
