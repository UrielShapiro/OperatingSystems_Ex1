#include "libpoisson.hpp"
#include <cmath>
#include <iostream>

// a simple recursive function to calculate factorial of a natural number
int factorial(unsigned int k)
{
    if (k == 0)
    {
        return 1;
    }
    return k * factorial(k - 1);
}

long double poisson(unsigned int k, long double lambda)
{
	// the Poisson distribution formula
    return (powl(lambda, k) * expl(-lambda)) / factorial(k);
}
