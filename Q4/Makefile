CXX = g++
CXXFLAGS = -Wall -Wextra -ggdb -g
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
LIB = libdijkstra
MAIN = main
TEST_MAIN = test
DOCTEST_PATH = . # path to doctest.h is in the current directory

all: $(MAIN) $(TEST_MAIN)

$(MAIN): $(MAIN).o $(LIB).o
	$(CXX) $(CXXFLAGS) -o $@ $^ -lgcov

$(MAIN).o: $(MAIN).cpp $(LIB).hpp  # Pattern rule for object files
	$(CXX) $(GCOV_FLAGS) $(CXXFLAGS) -c -o $@ $<

$(LIB).o: $(LIB).cpp $(LIB).hpp
	$(CXX) $(GCOV_FLAGS) $(CXXFLAGS) -c -o $@ $<


$(TEST_MAIN): Test.o TestMain.o $(LIB).o
	$(CXX) $(CXXFLAGS) -o $@ $^ -lgcov

Test.o: Test.cpp $(LIB).hpp  # Pattern rule for object files
	$(CXX) $(CXXFLAGS) -c -o $@ $<

TestMain.o: TestMain.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# $(MAIN): $(MAIN).o $(LIB).so
# 	$(CC) $(CPP_FLAGS) -o $@ $< $(LDFLAGS)

# $(MAIN).o: $(MAIN).cpp $(LIB).hpp  # Pattern rule for object files
# 	$(CC) $(CPP_FLAGS) -c -o $@ $<

# $(LIB).so: $(LIB).o
# 	$(CC) -shared -o $@ $<

	
# $(LIB).o: $(LIB).cpp $(LIB).hpp
# 	$(CC) $(CPP_FLAGS) -fPIC -o $@ $<

# $(TEST_MAIN): Test.o TestMain.o $(LIB).so
# 	$(CC) $(CPP_FLAGS) $(GCOV_FLAGS) -o $@ $^ $(LDFLAGS)

# Test.o: Test.cpp $(LIB).hpp  # Pattern rule for object files
# 	$(CC) $(CPP_FLAGS) -c -o $@ $<

# TestMain.o: TestMain.cpp
# 	$(CC) $(CPP_FLAGS) -c -o $@ $<

clean:
	rm -f *.o *.so *.gcov *.gcda *.gcno $(MAIN) $(TEST_MAIN)

.SUFFIXES:
.PHONY: all clean