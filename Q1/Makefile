CPP = g++
CPP_FLAGS = -Wall -Wextra -lm -ggdb
PROGS = DivisionByZeroException StackOverflowException UndefinedMemoryException

# compile all programs
all: $(PROGS)

# every file that ends in Exception is one of the programs and can be compiled with the appropriate cpp file
%Exception: %Exception.cpp
	$(CPP) $(CPP_FLAGS) -o $@ $<

clean:
	rm -f *.o *.so $(PROGS)

.SUFFIXES:
.PHONY: all clean
