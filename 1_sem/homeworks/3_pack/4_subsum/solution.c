#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

// Function to get the index of the maximum value in an array of size N
int get_index_max(int array[], int N)
{
    int index = 0, max = INT_MIN;
    for (int i = 0; i < N; i++)
    {
        if (array[i] > max)
        {
            max = array[i];
            index = i;
        }
    }
    return index;
}

int main(void)
{
    /* Redirect standard input to read from "input.txt" and standard output to "output.txt" */
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N;
    scanf("%d", &N); // Read the number of elements

    // Dynamically allocate memory for the array
    int *array = (int *)malloc(N * sizeof(int));

    // Variables to store the indices of the subarray with maximum sum
    int L = 0, R = 0;

    // Read the elements into the array
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &array[i]);
    }

    // Allocate memory for the left cumulative sums
    int *left_sums = (int *)malloc(N * sizeof(int));
    left_sums[0] = array[0]; // Initialize the first element of left_sums

    // Calculate cumulative sums from the left
    for (int i = 1; i < N; i++)
    {
        left_sums[i] = left_sums[i - 1] + array[i];
    }

    // Find the index of the maximum value in left_sums
    R = get_index_max(left_sums, N);
    free(left_sums); // Free the memory allocated for left_sums as it's no longer needed

    // Allocate memory for the right cumulative sums, up to the index R
    int *right_sums = (int *)malloc((R + 1) * sizeof(int));
    right_sums[R] = array[R]; // Initialize the last element of right_sums

    // Calculate cumulative sums from the right up to R
    for (int i = R - 1; i >= 0; i--)
    {
        right_sums[i] = right_sums[i + 1] + array[i];
    }

    // Find the index of the maximum value in right_sums within the range [0, R]
    L = get_index_max(right_sums, R + 1);

    // Output the results: L (start index), R (end index), and the maximum sum
    printf("%d %d %d\n", L, R, right_sums[L]);

    // Free the dynamically allocated memory
    free(right_sums);
    free(array);

    /* Close the file streams for input and output */
    fclose(stdin);
    fclose(stdout);

    return 0; // Successful program termination
}
