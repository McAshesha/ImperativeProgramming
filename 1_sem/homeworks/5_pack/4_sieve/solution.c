#include <stdio.h>
#include <stdlib.h>


int main()
{
    /* Redirect standard input to read from "input.txt" and standard output to "output.txt" */
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N, Q;
    scanf("%d %d", &N, &Q);

    int *not_prime_numbers = (int*) calloc(N, sizeof(int));

    not_prime_numbers[0] = 1;
    not_prime_numbers[1] = 1;

    for (int i = 2; i * i < N; i++)
    {
        if (!not_prime_numbers[i])
        {
            for (int j = i * i; j < N; j += i)
            {
                not_prime_numbers[j] = 1;
            }
        }
    }

    for (int i = 0; i < Q; i++)
    {
        int X;
        scanf("%d", &X);
        if (!not_prime_numbers[X])
        {
            printf("%d prime\n", X);
        }
        else
        {
            printf("%d not\n", X);
        }
    }

    /* Close the file streams for input and output */
    fclose(stdin);
    fclose(stdout);

    return 0;  // Exit the program
}
