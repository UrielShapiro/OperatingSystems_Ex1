#include <libpoisson.h>
#include <iostream>

int main()
{
    std::cout << "Pr(X = 1, \u03BB = 2) = " << poisson(1, 2) << std::endl;
    std::cout << "Pr(X = 10, \u03BB = 2) = " << poisson(10, 2) << std::endl;
    std::cout << "Pr(X = 2, \u03BB = 2) = " << poisson(2, 2) << std::endl;
    std::cout << "Pr(X = 3, \u03BB = 3) = " << poisson(3, 3) << std::endl;
    std::cout << "Pr(X = 3, \u03BB = 100) = " << poisson(3, 100) << std::endl;
    return 0;
}