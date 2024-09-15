#include <stdio.h>
#include <math.h>

int main(void)
{
    long long N; // Variable to store the input number

    /* Redirect standard input to read from "input.txt" and output to "output.txt" */
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    scanf("%lld", &N); // Read the input number

    long long count = 0; // Initialize counter to store the result

    // Outer loop iterates from 1 to the cube root of N
    for (long long i = 1; i <= cbrt(N); i++)
    {
        // Inner loop iterates from i to the square root of N/i
        for (long long j = i; j <= sqrt(N / i); j++)
        {
            // Calculate the number of possible k values for given i and j
            // Increment count by (N / (i * j) - j + 1), which represents valid k's
            count += N / (i * j) - j + 1;
        }
    }

    // Output the result
    printf("%lld\n", count);

    /* Close the file streams for input and output */
    fclose(stdin);
    fclose(stdout);

    return 0; // Indicate successful program termination
}
