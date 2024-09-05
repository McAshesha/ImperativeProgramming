#include <stdio.h>

int main(void)
{
    int N;

    /* Redirect standard input to read from "input.txt" and output to "output.txt" */
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    // Read the number of elements
    scanf("%d", &N);

    // Initialize counters for positive, negative, and neutral (zero) elements
    int count_positive = 0, count_negative = 0, count_neutral = 0;

    // Loop through each element
    for (int i = 0; i < N; i++)
    {
        int element;
        scanf("%d", &element); // Read each element

        // Categorize the element as positive, negative, or neutral (zero)
        if (element > 0)
        {
            count_positive++; // Increment positive counter
        }
        else if (element < 0)
        {
            count_negative++; // Increment negative counter
        }
        else
        {
            count_neutral++; // Increment neutral (zero) counter
        }
    }

    // Calculate and print the ratios with 5 decimal places
    printf("%.5lf %.5lf %.5lf\n",
           (double)count_negative / N,
           (double)count_neutral / N,
           (double)count_positive / N);

    /* Close the file streams for input and output */
    fclose(stdin);
    fclose(stdout);

    return 0; // Indicate successful program termination
}
