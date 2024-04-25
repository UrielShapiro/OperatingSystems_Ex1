CPP = g++
CPP_FLAGS = -Wall -Wextra -lm -ggdb
MAIN = dijkstra

all: $(MAIN)

$(MAIN): $(MAIN).o 
	$(CPP) $(CPP_FLAGS) -o $@ $< 

$(MAIN).o: $(MAIN).cpp
	$(CPP) $(CPP_FLAGS) -c -o $@ $<

clean:
	rm -f *.o *.so $(MAIN)

.SUFFIXES:
.PHONY: all clean