#include "modular.h"

int MOD;

int pnorm(int x)
{
    return (x % MOD + MOD) % MOD;
}

int padd(int a, int b)
{
    return pnorm(a + b);
}

int psub(int a, int b)
{
    return pnorm(a - b);
}

int pmul(int a, int b)
{
    int result = 0;
    a %= MOD;
    while (b > 0)
    {
        if (b % 2 == 1)
        {
            result = (result + a) % MOD;
        }
        a = (a * 2) % MOD;
        b /= 2;
    }
    return result;
}

int mod_inverse(int a)
{
    int mod = MOD;
    int m0 = mod, t, q;
    int x0 = 0, x1 = 1;
    if (mod == 1)
    {
        return 0;
    }
    while (a > 1)
    {
        q = a / mod;
        t = mod;
        mod = a % mod, a = t;
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

int pdiv(int a, int b)
{
    return pmul(a, mod_inverse(b));
}
