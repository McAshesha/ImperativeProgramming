#include <stdio.h>
#include <stdlib.h>

// Comparison function for qsort
int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b); // Return the difference between two integers
}

int main(void)
{
    /* Redirect standard input to read from "input.txt" and standard output to "output.txt" */
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N;
    scanf("%d", &N); // Read the number of elements

    // Dynamically allocate memory for the array
    int *array = (int *) malloc(N * sizeof(int));

    // Read the elements into the array
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &array[i]);
    }

    // Sort the array using qsort and the compare function
    qsort(array, N, sizeof(int), compare);

    // Print the sorted array
    for (int i = 0; i < N - 1; i++)
    {
        printf("%d ", array[i]);
    }
    // Print the last element separately to avoid a trailing space
    printf("%d\n", array[N - 1]);

    // Free the dynamically allocated memory
    free(array);

    /* Close the file streams for input and output */
    fclose(stdin);
    fclose(stdout);

    return 0; // Successful program termination
}
