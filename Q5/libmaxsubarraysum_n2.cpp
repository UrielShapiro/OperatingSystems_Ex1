#include <iostream>
#include <vector>

int maxSubArraySum(std::vector<int> arr)
{
    int maxSum = 0;
    for (size_t i = 0; i < arr.size(); i++)
    {
        int currentSum = 0;
        for (size_t j = i; j < arr.size(); j++)
        {
            currentSum += arr[j];
            maxSum = maxSum > currentSum ? maxSum : currentSum;
        }
    }
    return maxSum;
}