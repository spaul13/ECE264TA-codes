CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
TESTS = -DTEST_READ -DTEST_WRITE -DTEST_SORTID -DTEST_SORTFIRSTNAME -DTEST_SORTLASTNAME
GCC = gcc $(CFLAGS) $(TESTS)
OBJS =  pa06.o student.o msort.o
VALGRIND = valgrind --tool=memcheck --leak-check=yes --verbose

# This Makefile can be shortened by using loop. 
# It shows all steps to explain what it does

# test integrate1 using five different functions
# each function is tested using three sets of input data
pa06: $(OBJS) student.h msort.h
	$(GCC) $(OBJS) -o pa06

test: pa06
	./pa06 Problems/inputs/testinput1 id1 first1 last1
	#./pa06 Problems/inputs/testinput2 id2 first2 last2
	#./pa06 Problems/inputs/testinput2 id3 first3 last3

%.o: %.c 
	$(GCC) -c $<

clean:
	/bin/rm -f *.o
	/bin/rm -f *.gcda *.gcno gmon.out *gcov
	/bin/rm -f pa06
	/bin/rm -f id? first? last? log?


