#include <iostream>

int main()
{
    int* p = new int;
    *p = 1;
    delete p;
    std::cout << *p << std::endl;
    return 0;
}