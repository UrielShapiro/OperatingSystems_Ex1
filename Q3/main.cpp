#include "libpoisson.hpp"
#include <iostream>

int main()
{
	constexpr int COUNT = 5;
	double lambdas[COUNT] = {2.0f, 2.0f, 2.0f, 3.0f, 100.0f};
	int ks[COUNT] = {1, 10, 2, 3, 3};
	for (int i = 0; i < COUNT; ++i)
    	std::cout << "For X~Poi(" << lambdas[i] << "),\t Pr(X = " << ks[i] << ") = " << poisson(ks[i], lambdas[i]) << std::endl;
    return 0;
}
