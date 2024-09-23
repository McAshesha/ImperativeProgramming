#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    /* Redirect standard input to read from "input.txt" and standard output to "output.txt" */
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N;
    scanf("%d", &N);

    // Dynamically allocate an array to store the results, initialized to zero
    int *result = calloc(N, sizeof(int));

    // Read each element and update the result array
    for (int i = 1; i <= N; i++)
    {
        int element;
        scanf("%d", &element);

        // Update result array for divisors of i
        for (int j = 1; j <= N; j++)
        {
            if (i % j == 0) // Check if j is a divisor of i
            {
                result[j - 1] += element; // Accumulate the element in the corresponding position
            }
        }
    }

    // Output the results
    for (int i = 0; i < N; i++)
    {
        printf("%d\n", result[i]);
    }

    // Free the dynamically allocated memory
    free(result);

    /* Close the file streams for input and output */
    fclose(stdin);
    fclose(stdout);

    return 0; // Successful program termination
}
