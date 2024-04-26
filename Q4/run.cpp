#include <iostream>
#include <cstdlib>
/*
    This file is used to run the test cases, generate the gcov report and print the libdijkstra.cpp.gcov file.
    After running, the program will delete all executalbes and object files (as specified in the Makefile "clean").
*/
int main()
{
    system("make");
    system("./test");
    system("gcov libdijkstra.cpp");
    system("cat libdijkstra.cpp.gcov");
    system("make clean");
    return 0;
}