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

    int *arr = (int *) malloc(N * sizeof(int));

    for (int i = 0; i < N; i++)
    {
        scanf("%d", &arr[i]);
    }

    qsort(arr, N, sizeof(int), compare);

    int count = 0;

    for (int i = 0; i < N; i++)
    {
        if (arr[i] != arr[i + 1])
        {
            count++;
        }
    }

    printf("%d\n", count);

    for (int idx = 0, i = 0; i < N; i++)
    {
        if (arr[i] != arr[i + 1]) {
            printf("%d\n", arr[i]);
        }
    }

    free(arr);

    /* Close the file streams for input and output */
    fclose(stdin);
    fclose(stdout);

    return 0;
}
