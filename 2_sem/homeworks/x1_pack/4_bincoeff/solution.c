#include <stdio.h>

#define MAX_N 2001

int pascal_triangle[MAX_N][MAX_N];

void build_pascal_triangle(int n, int M)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            if (j == 0 || j == i)
            {
                pascal_triangle[i][j] = 1;
            }
            else
            {
                pascal_triangle[i][j] = (pascal_triangle[i - 1][j - 1] + pascal_triangle[i - 1][j]) % M;
            }
        }
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int M, T;
    scanf("%d %d", &M, &T);
    build_pascal_triangle(MAX_N, M);

    while (T--)
    {
        int N, K;
        scanf("%d %d", &N, &K);
        if (K < 0 || K > N)
        {
            printf("0\n");
        }
        else
        {
            printf("%d\n", pascal_triangle[N][K]);
        }
    }

    return 0;
}