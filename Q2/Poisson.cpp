#include <cmath>
#include <iostream>

/**
 * @brief Calculate the factorial of a number recursively
 * @return The factorial of the number k
*/
int factorial(int k)
{
    if (k == 0)
    {
        return 1;
    }
    return k * factorial(k - 1);
}

/**
 * @brief Calculate the poisson distribution of a number with a given lambda
*/
long double poisson(int k, double lambda)
{
    return (pow(lambda, k) * expf(-lambda)) / factorial(k);
}

int main(int argc, char **argv)
{
    if(argc != 3)                       // Exactly 3 arguments are required (program name, lambda, k)
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }
    double lambda = std::atof(argv[1]); // Parse the first argument as a double
    int k = std::atoi(argv[2]);         // Parse the second argument as an integer

    std::cout << "Pr(X = " << k << ") = " << poisson(k, lambda) << std::endl;
    return 0;
}
