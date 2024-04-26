#include <iostream>
#include <cstdlib>
/*
    * This file is used to run the test cases and generate the gcov report.
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