#include "libpoisson.hpp"
#include <cmath>
#include <iostream>

int factorial(int k)
{
    if (k == 0)
    {
        return 1;
    }
    return k * factorial(k - 1);
}

long double poisson(int k, double lambda)
{
    return (pow(lambda, k) * expf(-lambda)) / factorial(k);
}
