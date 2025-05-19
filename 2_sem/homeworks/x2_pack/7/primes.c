#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "primes.h"

#include <stdio.h>

char *not_primes = NULL;
int size = 0;

void build_sieve(int new_size)
{
    if (size >= new_size)
    {
        return;
    }
    else if (size == 0 || not_primes == NULL)
    {
        not_primes = (char *) calloc(new_size, sizeof(char));
        not_primes[0] = 1;
        not_primes[1] = 1;
    }
    else if (new_size > size)
    {
        not_primes = (char *) realloc(not_primes, new_size * sizeof(char));
        memset(not_primes + size, 0, (new_size - size) * sizeof(char));
    }

    for (int i = 2; i * i < new_size; i++)
    {
        if (!not_primes[i])
        {
            for (int j = i * i; j < new_size; j += i)
            {
                not_primes[j] = 1;
            }
        }
    }
    size = new_size;
}

int isPrime(int x)
{
    if (x == 2)
    {
        return 1;
    }
    if (x <= 1 || x & 1 == 0)
    {
        return 0;
    }

    build_sieve(x + 1);

    return !not_primes[x];
}

int findNextPrime(int x)
{
    if (x <= 2)
    {
        return 2;
    }

    build_sieve(x + (int) log(x) * 2);

    for (int i = x; i < size; i ++)
    {
        if (!not_primes[i])
        {
            return i;
        }
    }
}

int getPrimesCount(int l, int r)
{
    if (r <= 2)
    {
        return 0;
    }

    build_sieve(r);

    int count = 0;
    for (int i = l; i < r; i++)
    {
        if (!not_primes[i])
        {
            count++;
        }
    }

    return count;
}
