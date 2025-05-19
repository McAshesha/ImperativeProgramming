#include <stdio.h>
#include <stdint.h>

uint64_t bin_mod(uint64_t base, uint64_t exponent, uint64_t mod)
{
    uint64_t result = 0;
    base %= mod;
    while (exponent > 0)
    {
        if (exponent & 1)
        {
            result = (result + base) % mod;
        }
        base = (base * 2) % mod;
        exponent >>= 1;
    }
    return result;
}


uint64_t mod_inverse(uint64_t a, uint64_t m)
{
    long long m0 = m, t, q;
    long long x0 = 0, x1 = 1;

    if (m == 1)
    {
        return 0;
    }

    while (a > 1)
    {
        q = a / m;
        t = m;

        m = a % m;
        a = t;
        t = x0;

        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0)
    {
        x1 += m0;
    }

    return x1;
}

uint64_t solve(int k, uint64_t M[], uint64_t A[])
{
    uint64_t prod = 1;
    for (int i = 0; i < k; i++)
    {
        prod *= M[i];
    }

    uint64_t result = 0;
    for (int i = 0; i < k; i++)
    {
        uint64_t pp = prod / M[i];
        uint64_t inv = mod_inverse(pp, M[i]);
        uint64_t term = (A[i] * inv) % M[i];
        result = (result + bin_mod(term, pp, prod)) % prod;
    }

    return result;
}

int main()
{
    int k;
    scanf("%d", &k);
    uint64_t M[k], A[k];
    for (int i = 0; i < k; i++)
    {
        scanf("%llu", &M[i]);
    }
    for (int i = 0; i < k; i++)
    {
        scanf("%llu", &A[i]);
    }

    uint64_t X = solve(k, M, A);
    printf("%llu\n", X);

    return 0;
}
