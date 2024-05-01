#include <iostream>
#include <vector>

int maxSubArraySum(std::vector<int> arr)
{
    int maxSum = 0;
    for (size_t i = 0; i < arr.size(); i++)
    {
        for (size_t j = i; j < arr.size(); j++)
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