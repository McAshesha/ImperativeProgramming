typedef struct Factors
{
    int k;
    int primes[32];
    int powers[32];
}
Factors;

void Factorize(int X, Factors *res)
{
    res->k = 0;

    for (int p = 2; p * p <= X; p++)
    {
        if (X % p == 0)
        {
            int power = 0;
            while (X % p == 0)
            {
                X /= p;
                power++;
            }
            res->primes[res->k] = p;
            res->powers[res->k] = power;
            res->k++;
        }
    }

    if (X > 1)
    {
        res->primes[res->k] = X;
        res->powers[res->k] = 1;
        res->k++;
    }
}
