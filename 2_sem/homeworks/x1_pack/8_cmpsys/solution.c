#include <stdio.h>
#include <stdlib.h>

#define MAX 300
#define MOD 1000000007

void swap_rows(int i, int j, int cols, long long mat[MAX][MAX + 1])
{
    for (int c = 0; c <= cols; c++)
    {
        long long tmp = mat[i][c];
        mat[i][c] = mat[j][c];
        mat[j][c] = tmp;
    }
}

long long mod_inverse(long long a, long long p)
{
    long long old_r = a % p;
    if (old_r < 0)
    {
        old_r += p;
    }
    long long r = p;
    long long old_t = 1;
    long long t = 0;

    while (r != 0)
    {
        long long quotient = old_r / r;

        long long tmp = r;
        r = old_r - quotient * r;
        old_r = tmp;

        tmp = t;
        t = old_t - quotient * t;
        old_t = tmp;
    }

    return (old_r != 1) ? -1 : (old_t < 0 ? old_t + p : old_t);
}

long long bin_pow(long long base, long long exponent, long long mod)
{
    long long result = 1;
    base %= mod;
    while (exponent > 0)
    {
        if (exponent & 1)
        {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exponent >>= 1;
    }
    return result;
}

int gauss(int n, int k, long long P, long long mat[MAX][MAX + 1], int *rank)
{
    int current_row = 0;
    for (int col = 0; col < n && current_row < k; col++) {
        int pivot = -1;
        for (int i = current_row; i < k; i++)
        {
            if (mat[i][col] != 0)
            {
                pivot = i;
                break;
            }
        }
        if (pivot == -1)
        {
            continue;
        }

        swap_rows(current_row, pivot, n, mat);

        long long inv = mod_inverse(mat[current_row][col], P);
        if (inv == -1)
        {
            return -1;
        }

        for (int c = col; c <= n; c++)
        {
            mat[current_row][c] = (mat[current_row][c] * inv) % P;
            if (mat[current_row][c] < 0)
            {
                mat[current_row][c] += P;
            }
        }

        for (int i = 0; i < k; i++)
        {
            if (i != current_row && mat[i][col] != 0)
            {
                long long factor = mat[i][col];
                for (int c = col; c <= n; c++)
                {
                    mat[i][c] = (mat[i][c] - factor * mat[current_row][c]) % P;
                    if (mat[i][c] < 0) mat[i][c] += P;
                }
            }
        }
        current_row++;
    }

    for (int i = current_row; i < k; i++)
    {
        if (mat[i][n] != 0)
        {
            return 0;
        }
    }

    *rank = current_row;
    return (current_row < n) ? 2 : 1;
}

void back_substitute(int n, int k, long long mat[MAX][MAX + 1], long long P, long long result[MAX])
{
    for (int i = 0; i < n; i++)
    {
        result[i] = -1;
    }

    for (int i = 0; i < k; i++)
    {
        int col;
        for (col = 0; col < n; col++)
        {
            if (mat[i][col] != 0)
            {
                break;
            }
        }
        if (col < n)
        {
            result[col] = mat[i][n];
        }
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, k;
    long long P, mat[MAX][MAX + 1], result[MAX];
    scanf("%d %d %lld", &n, &k, &P);

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            scanf("%lld", &mat[i][j]);
            mat[i][j] %= P;
            if (mat[i][j] < 0) mat[i][j] += P;
        }
    }

    int rank;
    int res = gauss(n, k, P, mat, &rank);

    if (res == 0)
    {
        printf("0\n");
        return 0;
    }

    long long ans = bin_pow(P % MOD, n - rank, MOD);
    printf("%lld\n", ans);

    if (res == 1)
    {
        back_substitute(n, k, mat, P, result);
        for (int i = 0; i < n; i++)
        {
            printf("%lld\n", result[i]);
        }
    }

    return 0;
}