CPP = g++
CPP_FLAGS = -Wall -Wextra -lm
PROG = Poisson
all: $(PROG)

$(PROG): $(PROG).cpp
	$(CPP) $(CPP_FLAGS) -o $@ $<

clean:
	rm -f $(PROG)

.SUFFIXES:
.PHONY: all clean
