#include <stdio.h>
#include <limits.h>
#include <stdlib.h>


int find_min_index(int n, long long A[], long long C)
{
    int min_index = 0;
    long long min_value = A[0] + C * 0;

    for (int i = 1; i < n; i++)
    {
        long long value = A[i] + C * i;
        if (value < min_value)
        {
            min_value = value;
            min_index = i;
        }
    }
    return min_index;
}


int main()
{
    /* Redirect standard input to read from "input.txt" and output to "output.txt" */
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, q;

    scanf("%d", &n);
    long long *A = (long long *) malloc(n * sizeof(long long));

    for (int i = 0; i < n; i++)
    {
        scanf("%lld", &A[i]);
    }

    scanf("%d", &q);
    long long *C = (long long *) malloc(q * sizeof(long long));

    for (int j = 0; j < q; j++)
    {
        scanf("%lld", &C[j]);
    }

    for (int j = 0; j < q; j++)
    {
        printf("%d\n", find_min_index(n, A, C[j]));
    }

    free(A);
    free(C);

    /* Close the file streams for input and output */
    fclose(stdin);
    fclose(stdout);
    return 0;
}
