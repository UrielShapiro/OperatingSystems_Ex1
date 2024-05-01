#include <iostream>
#include <climits>
#include <vector>

#define MINUS_INF INT_MIN

int maxSubArraySum(int arr[], size_t n)
{
    int maxSum = 0, currentSum = 0;
    for (size_t k = 0; k < n; k++)
    {
        currentSum = arr[k] > (currentSum + arr[k]) ? arr[k] : (currentSum + arr[k]);
        maxSum = maxSum > currentSum ? maxSum : currentSum;
    }
    return maxSum;
}