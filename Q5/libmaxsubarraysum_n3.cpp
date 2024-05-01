#include <iostream>
#include <vector>

int maxSubArraySum(int arr[], size_t n)
{
    int maxSum = 0;
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = i; j < n; j++)
        {
            int currentSum = 0;
            for (size_t k = i; k <= j; k++)
            {
                currentSum += arr[k];
            }
            maxSum = maxSum > currentSum ? maxSum : currentSum;
        }
    }
    return maxSum;
}