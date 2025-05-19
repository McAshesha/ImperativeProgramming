#include <stdint.h>

extern int64_t Sum(int l, int r);
extern int N;

int Query(int l, int64_t sum)
{
    int low = l;
    int high = N;
    int result = l;

    while (low <= high)
    {
        int mid = (high + low) / 2;
        int64_t currentSum = Sum(l, mid);

        if (currentSum <= sum)
        {
            result = mid;
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return result;
}
