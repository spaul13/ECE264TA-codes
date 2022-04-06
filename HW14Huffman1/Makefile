# ***
# *** Please modify this file and check what would happen
# ***

WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR) 
# This is a comment (starting with #)
SRCS = main.c list.c tree.c

# object files are created by converting .c to .o
OBJS = $(SRCS:%.c=%.o)

main: $(OBJS) 
	$(GCC) $(TESTFLAGS) $(OBJS) -o main

.c.o: 
	$(GCC) $(TESTFLAGS) -c $*.c 


clean: # remove all machine generated files
	rm -f main *.o *.out *gcda *gcno *gcov

