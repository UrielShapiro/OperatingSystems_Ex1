CPP = g++
PROG = Poisson
all: $(PROG)

$(PROG): $(PROG).cpp
	$(CPP) -o $@ $< -lm

clean:
	rm $(PROG)

.SUFFIXES:
.PHONY: all clean
