CPP = g++
CPP_FLAGS = -Wall -Wextra -ggdb -g
GCOV_FLAGS = -fprofile-arcs -ftest-coverage -lncurses
MAIN = dijkstra

all: $(MAIN) test

$(MAIN): $(MAIN).o 
	$(CPP) $(CPP_FLAGS) -o $@ $< 

$(MAIN).o: $(MAIN).cpp
	$(CPP) $(CPP_FLAGS) -c -o $@ $<

test: Test.o TestMain.o
	$(CXX) $(GCOV_FLAGS) $(CXXFLAGS) $^ -o test

Test.o: Test.cpp
	$(CXX) $(CXXFLAGS) -c $<

TestMain.o: TestMain.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o *.so *.gcov *.gcda *.gcno $(MAIN) test

.SUFFIXES:
.PHONY: all clean