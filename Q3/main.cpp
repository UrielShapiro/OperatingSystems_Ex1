#include "libpoisson.hpp"
#include <iostream>

int main()
{
	// create arrays of the required values in respective places
	constexpr int COUNT = 5;
	long double lambdas[COUNT] = {2.0f, 2.0f, 2.0f, 3.0f, 100.0f};
	unsigned int ks[COUNT] = {1, 10, 2, 3, 3};
	// iterate through the arrays
	for (int i = 0; i < COUNT; ++i)
		// print the result of the function
		std::cout << "For X~Poi(" << lambdas[i] << "),\t Pr(X = " << ks[i] << ") = "
				  << poisson(ks[i], lambdas[i]) << std::endl;
    return 0;
}
