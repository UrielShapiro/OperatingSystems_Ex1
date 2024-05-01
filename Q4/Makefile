CXX = g++
CXXFLAGS = -Wall -Wextra -ggdb -g
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
LIB = libdijkstra
MAIN = main
TEST_MAIN = test
DOCTEST_PATH = . # path to doctest.h is in the current directory

all: $(MAIN) $(TEST_MAIN)


run:
	make all
	./$(TEST_MAIN)
	gcov $(LIB).cpp
	cat $(LIB).cpp.gcov
	make clean

$(MAIN): $(MAIN).o $(LIB).o
	$(CXX) $(CXXFLAGS) -o $@ $^ -lgcov

$(MAIN).o: $(MAIN).cpp $(LIB).hpp
	$(CXX) $(GCOV_FLAGS) $(CXXFLAGS) -c -o $@ $<

$(LIB).o: $(LIB).cpp $(LIB).hpp
	$(CXX) $(GCOV_FLAGS) $(CXXFLAGS) -c -o $@ $<


$(TEST_MAIN): Test.o TestMain.o $(LIB).o
	$(CXX) $(CXXFLAGS) -o $@ $^ -lgcov

Test.o: Test.cpp $(LIB).hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

TestMain.o: TestMain.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<


clean:
	rm -f *.o *.so *.gcov *.gcda *.gcno $(MAIN) $(TEST_MAIN) run

.SUFFIXES:
.PHONY: all clean run
