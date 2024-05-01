#include <iostream>

/*
    * This function calculates the maximum subarray sum of an array of integers in O(n^2).
    * @returns the maximum subarray sum.
*/
int maxSubArraySum(int arr[], size_t n)
{
    int maxSum = 0;
    for (size_t i = 0; i < n; i++)
    {
        int currentSum = 0;
        for (size_t j = i; j < n; j++)
        {
            currentSum += arr[j];
            maxSum = maxSum > currentSum ? maxSum : currentSum;
        }
    }
    return maxSum;
}