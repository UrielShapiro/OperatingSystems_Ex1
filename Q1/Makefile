CPP = g++
CPP_FLAGS = -Wall -Wextra -lm -ggdb
PROGS = DivisionByZeroException StackOverflowException UndefinedMemoryException

all: $(PROGS)

%Exception: %Exception.cpp
	$(CPP) $(CPP_FLAGS) -o $@ $<

clean:
	rm -f *.o *.so $(PROGS)

.SUFFIXES:
.PHONY: all clean
