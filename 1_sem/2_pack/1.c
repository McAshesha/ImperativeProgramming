#include <stdio.h>
#include <math.h>


int is_prime(int number)
{
    for (int i = 2; i <= sqrt(number); i++)
    {
        if (number % i == 0) // If number is divisible by i, it's not prime
        {
            return 0;
        }
    }

    return 1;
}


int main(void)
{
    int N;

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    scanf("%d", &N);

    for (int i = 2; i <= N; i++)
    {
        if (is_prime(i))
        {
            printf("%d\n", i);
        }
    }

    fclose(stdin);
    fclose(stdout);

    return 0; // Indicate successful program termination
}
