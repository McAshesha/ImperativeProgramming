#include <stdio.h>

int main(void) // Main function
{
    int N; // Variable to store the user's input

    /* Redirect standard input to read from "input.txt" and output to "output.txt" */
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    scanf("%d", &N); // Reading the input number from the user

    int result = 0; // Initialize the result variable to store the sum
    for (int i = 1; i <= N; i++) // Loop from 1 to the input number
    {
        result += i; // Add the current value of i to the result
    }

    printf("%d\n", result); // Output the result of the sum

    /* Close the file streams for input and output */
    fclose(stdin);
    fclose(stdout);

    return 0; // Indicate that the program ended successfully
}
