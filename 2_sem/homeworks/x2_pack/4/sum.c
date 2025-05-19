#include <stdint.h>

static int64_t prefixSum[100001];

void Init(const int *arr, int k)
{
    prefixSum[0] = arr[0];
    for (int i = 1; i < k; i++)
    {
        prefixSum[i] = prefixSum[i - 1] + arr[i];
    }
}

int64_t Sum(int l, int r)
{
    if (l == 0)
    {
        return prefixSum[r - 1];
    }
    return prefixSum[r - 1] - prefixSum[l - 1];
}
