CPP = g++
CPP_FLAGS = -Wall -Wextra -lm -ggdb
MAIN = main
LIB = libpoisson

# compile the main program
all: $(MAIN)

# compile the program using the main object file and the shared library by linking with it
$(MAIN): $(MAIN).o $(LIB).so
	$(CPP) $(CPP_FLAGS) -o $@ $< -lpoisson -L.

$(MAIN).o: $(MAIN).cpp $(LIB).hpp
	$(CPP) $(CPP_FLAGS) -c -o $@ $<

# compile the shared library with position independent code
$(LIB).so: $(LIB).cpp $(LIB).hpp
	$(CPP) $(CPP_FLAGS) -c -fPIC -o $@ $<

clean:
	rm -f *.o *.so $(MAIN)

.SUFFIXES:
.PHONY: all clean
