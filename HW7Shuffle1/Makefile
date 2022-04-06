# Makefile

EXEC1 = hw7_1
EXEC2 = hw7_2
EXEC3 = hw7_3
EXEC4 = hw7_4

WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Wno-cpp
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)

TESTFLAGS = -DTEST_DIVIDE -DTEST_INTERLEAVE -DTEST_SHUFFLE


VALGRIND = valgrind --tool=memcheck --verbose

$(EXEC1):
	$(GCC) main.c shuffle.c -o $(EXEC1) $(TESTFLAGS)

$(EXEC2):
	$(GCC) main.c shuffle.c expected.c -o $(EXEC2) -DTEST_INTERLEAVE -DTEST_SHUFFLE

$(EXEC3):
	$(GCC) main.c shuffle.c expected.c -o $(EXEC3) -DTEST_DIVIDE -DTEST_SHUFFLE

$(EXEC4):
	$(GCC) main.c shuffle.c expected.c -o $(EXEC4) -DTEST_DIVIDE -DTEST_INTERLEAVE


test1: $(EXEC1)
	./$(EXEC1) 4 | sort > output4
	diff -w output4 expected/expected4

test2: $(EXEC1)
	./$(EXEC1) 8 | sort > output8
	diff -w output8 expected/expected8

test3: $(EXEC1)
	./$(EXEC1) 11 | sort > output11
	diff -w output11 expected/expected11

test4: $(EXEC2)
	./$(EXEC2) 4 | sort > output4
	diff -w output4 expected/expected4

test5: $(EXEC2)
	./$(EXEC2) 8 | sort > output8
	diff -w output8 expected/expected8

test6: $(EXEC2)
	./$(EXEC2) 11 | sort > output11
	diff -w output11 expected/expected11

test7: $(EXEC3)
	./$(EXEC3) 4 | sort > output4
	diff -w output4 expected/expected4

test8: $(EXEC3)
	./$(EXEC3) 8 | sort > output8
	diff -w output8 expected/expected8

test9: $(EXEC3)
	./$(EXEC3) 11 | sort > output11
	diff -w output11 expected/expected11

test10: $(EXEC4)
	./$(EXEC4) 4 | sort > output4
	diff -w output4 expected/expected4

test11: $(EXEC4)
	./$(EXEC4) 8 | sort > output8
	diff -w output8 expected/expected8

test12: $(EXEC4)
	./$(EXEC4) 11 | sort > output11
	diff -w output11 expected/expected11

test13: $(EXEC1)
	$(VALGRIND) ./$(EXEC1) 4

clean:
	rm -f $(OBJS) $(TARGET) output* logfile

