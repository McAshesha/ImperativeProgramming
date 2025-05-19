#include <stdio.h>

typedef struct Factors
{
    int k;
    int primes[32];
    int powers[32];
} Factors;

void Factorize(int X, struct Factors *res);

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int M;
    scanf("%d", &M);

    for (int i = 0; i < M; i++)
    {
        int X;
        scanf("%d", &X);

        Factors res;
        Factorize(X, &res);

        printf("%d =", X);
        if (res.k == 0)
        {
            printf(" 1\n");
        }
        else
        {
            for (int j = 0; j < res.k; j++)
            {
                printf(" %d^%d", res.primes[j], res.powers[j]);
                if (j < res.k - 1)
                {
                    printf(" *");
                }
            }
            printf("\n");
        }
    }

    return 0;
}
