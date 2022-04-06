# Makefile

TARGET = hw11
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)

TESTFLAGS = -DTEST_DIVIDE -DTEST_INTERLEAVE -DTEST_SHUFFLE

SRCS =  main.c shuffle.c

OBJS = $(SRCS:%.c=%.o)

VALGRIND = valgrind --tool=memcheck --verbose --log-file

$(TARGET): $(OBJS)
	$(GCC) $(TESTFLAGS) $(OBJS) -o $(TARGET)

memory: $(TARGET)
	$(VALGRIND)=./logfile ./hw11 4

testall: test31 test32 test42 test62

test31: $(TARGET)
	./hw11 3 1 | sort > output31
	diff -w output31 expected/expected31

test32: $(TARGET)
	./hw11 3 2 | sort > output32
	diff -w output32 expected/expected32

test42: $(TARGET)
	./hw11 4 2 | sort > output42
	diff -w output42 expected/expected42

test62: $(TARGET)
	./hw11 6 2 | sort > output62
	diff -w output62 expected/expected62

.c.o:
	$(GCC) $(CFLAGS) $(TESTFLAGS) -c $*.c

clean:
	rm -f $(OBJS) $(TARGET) output* logfile

