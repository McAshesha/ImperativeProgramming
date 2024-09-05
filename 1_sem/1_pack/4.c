#include <math.h>
#include <stdio.h>

int main(void)
{
    int N; // Variable to store the input number

    /* Redirect standard input to read from "input.txt" and output to "output.txt" */
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    scanf("%d", &N); // Read the input number

    // Handle the special case where the number is 1
    if (N == 1)
    {
        printf("NO\n"); // 1 is not a prime number
        return 0;
    }

    // Check divisibility from 2 up to the square root of the number
    for (int i = 2; i <= sqrt(N); i++)
    {
        if (N % i == 0) // If number is divisible by i, it's not prime
        {
            printf("NO\n");
            return 0;
        }
    }

    printf("YES\n"); // If no divisors were found, the number is prime

    /* Close the file streams for input and output */
    fclose(stdin);
    fclose(stdout);

    return 0; // Indicate that the program ended successfully
}
