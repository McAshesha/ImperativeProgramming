#include <stdio.h>

#define MAX_VALUE 10000 // Define the maximum possible value in the input

int main(void)
{
    /* Redirect standard input to read from "input.txt" and standard output to "output.txt" */
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N;
    scanf("%d", &N); // Read the number of elements

    int result[MAX_VALUE + 1] = {0}; // Array to store the frequency of each number, initialized to 0

    // Loop through the input elements and count their occurrences
    for (int i = 0; i < N; i++)
    {
        int element;
        scanf("%d", &element); // Read the element
        result[element]++; // Increment the count for this element
    }

    // Loop through the result array to print non-zero frequencies
    for (int i = 1; i <= MAX_VALUE; i++)
    {
        if (result[i] != 0) // Only print if the element has appeared at least once
        {
            printf("%d: %d\n", i, result[i]); // Output the element and its frequency
        }
    }

    /* Close the file streams for input and output */
    fclose(stdin);
    fclose(stdout);

    return 0; // Successful program termination
}
