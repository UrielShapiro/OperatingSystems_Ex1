#include <iostream>
#include <vector>

int maxSubArraySum(int[], size_t);

/*
    * This function generates an array of random integers.
    * @returns a pointer to the array.
*/
int* create_random_input(unsigned long seed, size_t n)
{
    int* result = new int[n];
    srand(seed);
    for (size_t i = 0; i < n; ++i)
    {
        result[i] = (rand() % 100) - 25;
    }
    return result;
}

int main(int argc, char **argv)
{
    char *program = argv[0];
    if (argc < 3)
    {
        std::cerr << "Error: Provide at least 2 arguments" << std::endl;
        std::cerr << "Usage: " << program << " <seed> <n>" << std::endl;
        return 1;
    }
    unsigned int seed = atoi(argv[1]);  // Parse the seed from the command line
    size_t n = atoi(argv[2]);           

    auto arr = create_random_input(seed, n);
    int result = maxSubArraySum(arr,n);
    std::cout << "The result is " << result << std::endl;
    delete[] arr;
    return 0;
}