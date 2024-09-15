#include <stdio.h>

int main(void)
{
    int A, B; // Variables to store the input numbers

    /* Redirect standard input to read from "input.txt" and output to "output.txt" */
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    scanf("%d %d", &A, &B); // Read the input values

    // Calculate the floor division result
    int floor = (A % B == 0 || A > 0) ? A / B : A / B - 1;

    // Calculate the ceiling division result
    int ceil = (A % B == 0 || A < 0) ? A / B : A / B + 1;

    // Truncated division result (equivalent to standard division)
    int trunc = A / B;

    // Calculate the remainder, ensuring it's always non-negative
    int remainder = (A % B + B) % B;

    // Output the results: floor, ceiling, truncated division, and remainder
    printf("%d %d %d %d\n", floor, ceil, trunc, remainder);

    /* Close the file streams for input and output */
    fclose(stdin);
    fclose(stdout);

    return 0; // Indicate successful program termination
}
