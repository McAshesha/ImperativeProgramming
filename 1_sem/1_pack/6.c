#include <limits.h>
#include <stdio.h>

int main(void)
{
    int N; // Variable to store the number of elements

    /* Redirect standard input to read from "input.txt" and output to "output.txt" */
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    scanf("%d", &N); // Read the number of elements

    // Initialize min and max values with extreme possible values
    int min = INT_MAX, index_min = 0; // `min` stores the smallest element, `index_min` its position
    int max = INT_MIN, index_max = 0; // `max` stores the largest element, `index_max` its position

    // Loop through each element
    for (int i = 1; i <= N; i++)
    {
        int element; // Variable to store the current element
        scanf("%d", &element); // Read the current element

        // Check if the current element is smaller than the current min
        if (element < min)
        {
            min = element; // Update the min value
            index_min = i; // Update the index of the min value
        }

        // Check if the current element is larger than the current max
        if (element > max)
        {
            max = element; // Update the max value
            index_max = i; // Update the index of the max value
        }
    }

    // Output the min value, its position, the max value, and its position
    printf("%d %d %d %d\n", min, index_min, max, index_max);

    /* Close the file streams for input and output */
    fclose(stdin);
    fclose(stdout);

    return 0; // Indicate successful program termination
}
