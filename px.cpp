#include <libpoisson.h>
#include <iostream>

int main(int argc, char** argv)
{
    if(argc != 3)
    {
        std::cout << "Error\n" << std::endl;
        return 1;
    }
    int k = std::atoi(argv[1]);
    double lambda = std::atof(argv[2]);

    std::cout << "Pr(X = " << k << ") = " << poisson(k, lambda) << std::endl;
    return 0;
}