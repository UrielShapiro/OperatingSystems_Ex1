#include <iostream>

// forward decleration of the function implemented in the libraries
// this is instead of writing a very small header file
// an example for such header file can be seen in question 3
int maxSubArraySum(int[], size_t);

/**
 * This function generates an array of random integers in a predefined range.
 * The array is dynamically allocated and must later be deleted.
 * @param seed the initial seed of the randomized
 * @param n the size of the wanted array
 * @returns a pointer to the array.
 */
int *create_random_input(unsigned long seed, size_t n)
{
    int *result = new int[n];
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
    unsigned int seed = atoi(argv[1]);  // Parse the seed from the arguments
    size_t n = atoi(argv[2]);           // Parse n from the arguments

	// create a random array with the argument parameters
    auto arr = create_random_input(seed, n);
	// calculate the result using the linked library
    int result = maxSubArraySum(arr,n);
	// print the result to validate correctness
    std::cout << "The result is " << result << std::endl;
	// free the array allocated by create_random_input
    delete[] arr;
    return 0;
}
