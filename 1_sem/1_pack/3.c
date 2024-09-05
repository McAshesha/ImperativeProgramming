#include <stdio.h>

int main(void)
{
    int N; // Variable to store the number of elements

    /* Redirect standard input to read from "input.txt" and output to "output.txt" */
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    scanf("%d", &N); // Read the number of elements

    int result = 0; // Variable to accumulate the sum of even elements

    for (int i = 0; i < N; i++) // Loop through each element
    {
        int element; // Variable to store the current element
        scanf("%d", &element); // Read the current element

        if (element % 2 == 0) // Check if the element is even
        {
            result += element; // Add even element to the result
        }
    }

    printf("%d\n", result); // Output the sum of even elements

    /* Close the file streams for input and output */
    fclose(stdin);
    fclose(stdout);

    return 0; // Indicate successful program termination
}
