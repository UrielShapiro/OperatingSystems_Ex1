CPP = g++
CPP_FLAGS = -Wall -Wextra -lm -ggdb
MAIN = main
LIB = libpoisson

all: $(MAIN)

$(MAIN): $(MAIN).o $(LIB).so
	$(CPP) $(CPP_FLAGS) -o $@ $< -lpoisson -L.

$(MAIN).o: $(MAIN).cpp $(LIB).hpp
	$(CPP) $(CPP_FLAGS) -c -o $@ $<

$(LIB).so: $(LIB).cpp $(LIB).hpp
	$(CPP) $(CPP_FLAGS) -c -fPIC -o $@ $<

clean:
	rm -f *.o *.so $(MAIN)

.SUFFIXES:
.PHONY: all clean
