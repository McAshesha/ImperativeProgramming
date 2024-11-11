#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b)
{
    return *(int *) a - *(int *) b;
}

int main()
{
    /* Redirect standard input to read from "input.txt" and standard output to "output.txt" */
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N;
    scanf("%d", &N);

    int *a = (int*) malloc(N * sizeof(int));
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &a[i]);
    }

    qsort(a, N, sizeof(int), compare);
    long long sum_min = 0;
    for (int i = 0; i < N - 1; i++)
    {
        sum_min += (long long) a[i] * (N - i - 1);
    }

    printf("%lld", sum_min);
    free(a);

    /* Close the file streams for input and output */
    fclose(stdin);
    fclose(stdout);
    return 0;
}
