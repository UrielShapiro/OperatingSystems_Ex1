CPP = g++
CPP_FLAGS = -Wall -Wextra -ggdb -g -pg

# the main executable's source
MAIN = main
# the library's source
LIB = libmaxsubarraysum

# compile executables for each of the library implementations
all: main_n main_n2 main_n3

# this rule profiles on all required cases
# it prerequires all to compile the executables
# then it runs all cases and gprofs the output into appropriate text files
profile: all
	mkdir -p results

	./main_n 100 100
	gprof ./main_n > results/n_100.txt
	./main_n 1000 1000
	gprof ./main_n > results/n_1000.txt
	./main_n 10000 10000
	gprof ./main_n > results/n_10000.txt

	./main_n2 100 100
	gprof ./main_n2 > results/n2_100.txt
	./main_n2 1000 1000
	gprof ./main_n2 > results/n2_1000.txt
	./main_n2 10000 10000
	gprof ./main_n2 > results/n2_10000.txt

	./main_n3 100 100
	gprof ./main_n3 > results/n3_100.txt
	./main_n3 1000 1000
	gprof ./main_n3 > results/n3_1000.txt
	./main_n3 10000 10000
	gprof ./main_n3 > results/n3_10000.txt

# to compile an executable, use the main object and the appropriate object according to the name
$(MAIN)_%: $(MAIN).o $(LIB)_%.o
	$(CPP) $(CPP_FLAGS) -o $@ $^

$(MAIN).o: $(MAIN).cpp
	$(CPP) -c $(CPP_FLAGS) -o $@ $<

# for any library implementation use the same name cpp file
$(LIB)_%.o: $(LIB)_%.cpp
	$(CPP) -c $(CPP_FLAGS) $< -o $@

clean:
	rm -f *.o $(MAIN)_* gmon.out

.SUFFIXES:
.PHONY: all clean profile
