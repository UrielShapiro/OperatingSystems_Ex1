CXX = g++
CXXFLAGS = -Wall -Wextra -ggdb -g
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
LIB = libdijkstra
MAIN = main
TEST = Test
DOCTEST_PATH = . # path to doctest.h is in the current directory

all: $(MAIN) $(TEST)


run:
	make all
	./$(TEST)
	gcov $(LIB).cpp
	cat $(LIB).cpp.gcov
	make clean

$(MAIN): $(MAIN).o $(LIB).o
	$(CXX) $(CXXFLAGS) -o $@ $^ -lgcov

$(MAIN).o: $(MAIN).cpp $(LIB).hpp
	$(CXX) $(GCOV_FLAGS) $(CXXFLAGS) -c -o $@ $<

$(LIB).o: $(LIB).cpp $(LIB).hpp
	$(CXX) $(GCOV_FLAGS) $(CXXFLAGS) -c -o $@ $<


test: $(TEST)

$(TEST): $(TEST).o $(LIB).o
	$(CXX) $(CXXFLAGS) -o $@ $^ -lgcov

$(TEST).o: $(TEST).cpp $(LIB).hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f *.o *.so *.gcov *.gcda *.gcno $(MAIN) $(TEST) run

.SUFFIXES:
.PHONY: all clean run test
