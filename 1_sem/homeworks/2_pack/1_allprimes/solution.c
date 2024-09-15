#include <stdio.h>

// Function to check if a number is prime
int is_prime(int number)
{
    // Loop to check divisibility from 2 to the square root of the number
    for (int i = 2; i * i <= number; i++)
    {
        if (number % i == 0) // If divisible by any number, it's not prime
        {
            return 0;
        }
    }

    return 1; // If no divisors found, it's prime
}

int main(void)
{
    int N;

    /* Redirect standard input to read from "input.txt" and output to "output.txt" */
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    // Read the number N from the input file
    scanf("%d", &N);

    // Loop through numbers from 2 to N to check for primes
    for (int i = 2; i <= N; i++)
    {
        // If the number is prime, print it
        if (is_prime(i))
        {
            printf("%d\n", i); // Output prime numbers to "output.txt"
        }
    }

    /* Close the file streams for input and output */
    fclose(stdin);
    fclose(stdout);

    return 0; // Indicate successful program termination
}
