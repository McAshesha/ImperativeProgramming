#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007
#define MAX 1000000

long long fact[MAX + 1];
long long r_fact[MAX + 1];

long long bin_pow(long long a, long long exp)
{
    long long res = 1;
    a %= MOD;
    while (exp > 0)
    {
        if (exp & 1)
        {
            res = (res * a) % MOD;
        }
        a = (a * a) % MOD;
        exp >>= 1;
    }
    return res;
}

void build_facts()
{
    fact[0] = 1;
    for (int i = 1; i <= MAX; i++)
    {
        fact[i] = (i * fact[i - 1]) % MOD;
    }

    r_fact[MAX] = bin_pow(fact[MAX], MOD - 2);
    for (int i = MAX; i >= 1; i--)
    {
        r_fact[i - 1] = (r_fact[i] * i) % MOD;
    }
}

long long bin_coeff(int n, int k)
{
    return ((fact[n] * r_fact[n - k]) % MOD * r_fact[k]) % MOD;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int T;
    scanf("%d", &T);
    build_facts();

    while (T--)
    {
        int N, K;
        scanf("%d %d", &N, &K);
        printf("%lld\n", bin_coeff(N, K));
    }

    return 0;
}
