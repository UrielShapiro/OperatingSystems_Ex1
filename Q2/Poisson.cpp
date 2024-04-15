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

int main(int argc, char **argv)
{
    if(argc != 3)
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }
    double lambda = std::atof(argv[1]);
    int k = std::atoi(argv[2]);

    std::cout << "Pr(X = " << k << ") = " << poisson(k, lambda) << std::endl;
    return 0;
}
