#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b)
{
    return *(int*) a - *(int*) b;
}

int remove_duplicates(int *arr, int n)
{
    if (n <= 1)
    {
        return n;
    }
    int idx = 0;
    for (int i = 0; i < n - 1; i++)
    {
        if (arr[i] != arr[i + 1])
        {
            arr[idx++] = arr[i];
        }
    }
    arr[idx++] = arr[n - 1];
    return idx;
}

void print_unique_values(int *A, int nA, int *B, int nB)
{
    qsort(B, nB, sizeof(int), compare);

    int *foundValues = malloc(nA * sizeof(int));
    int foundCount = 0;

    for (int i = 0; i < nA; i++)
    {
        if (bsearch(&A[i], B, nB, sizeof(int), compare) == NULL)
        {
            foundValues[foundCount++] = A[i];
        }
    }

    qsort(foundValues, foundCount, sizeof(int), compare);
    foundCount = remove_duplicates(foundValues, foundCount);

    printf("%d\n", foundCount);
    for (int i = 0; i < foundCount; i++)
    {
        printf("%d ", foundValues[i]);
    }
    printf("\n");

    free(foundValues);
}

int main() {
    /* Redirect standard input to read from "input.txt" and output to "output.txt" */
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int nA, nB;

    scanf("%d", &nA);

    int *A = malloc(nA * sizeof(int));
    for (int i = 0; i < nA; i++)
    {
        scanf("%d", &A[i]);
    }

    scanf("%d", &nB);

    int *B = malloc(nB * sizeof(int));
    for (int i = 0; i < nB; i++)
    {
        scanf("%d", &B[i]);
    }

    print_unique_values(A, nA, B, nB);

    free(A);
    free(B);

    /* Close the file streams for input and output */
    fclose(stdin);
    fclose(stdout);

    return 0;
}
