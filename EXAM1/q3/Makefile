CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
GCC = gcc $(CFLAGS)
EXEC = q3prog
TESTFLAGS = -DTEST_COMPARE

SRCS = add.c compare.c main.c 
OBJS = $(SRCS:%.c=%.o)
# <--- Question A: What is the value of OBJS? --->

all: $(EXEC)

# link .o to executable
$(EXEC): $(OBJS)
	# <--- Question B: Fix the following --->
	$(GCC) $(TESTFLAGS) $(OBJS)    [ANSWER B]    $(EXEC)

# convert .c to .o 
%.o: %.c
	$(GCC) $(TESTFLAGS) -c $<

testall: test1 test2 test3

test1: $(EXEC)
	./$(EXEC) inputs/input1 > output1

test2: $(EXEC)
	./$(EXEC) inputs/input2 > output2

test3: $(EXEC)
	./$(EXEC) inputs/input3 > output3

clean: # remove all machine generated files
	rm -f $(EXEC) *.o *.out *gcda *gcno *gcov
