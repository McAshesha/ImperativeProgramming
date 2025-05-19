#include <stdio.h>
#include <math.h>

#define MAX 200
#define EPSILON 1e-3

void solveGauss(int n, double mat[MAX][MAX + 1], double result[MAX])
{
    int i, j, k;
    double factor;

    for (i = 0; i < n; i++)
    {
        if (fabs(mat[i][i]) < EPSILON)
        {
            for (j = i + 1; j < n; j++)
            {
                if (fabs(mat[j][i]) > EPSILON)
                {
                    for (k = i; k <= n; k++)
                    {
                        double temp = mat[i][k];
                        mat[i][k] = mat[j][k];
                        mat[j][k] = temp;
                    }
                    break;
                }
            }
        }

        if (fabs(mat[i][i]) > EPSILON)
        {
            for (j = i + 1; j < n; j++)
            {
                factor = mat[j][i] / mat[i][i];
                for (k = i; k <= n; k++)
                {
                    mat[j][k] -= factor * mat[i][k];
                }
            }
        }
    }

    for (i = n - 1; i >= 0; i--)
    {
        result[i] = mat[i][n];
        for (j = i + 1; j < n; j++)
        {
            result[i] -= mat[i][j] * result[j];
        }
        result[i] /= mat[i][i];
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, i, j;
    double mat[MAX][MAX + 1];
    double result[MAX];

    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        for (j = 0; j <= n; j++)
        {
            scanf("%lf", &mat[i][j]);
        }
    }

    solveGauss(n, mat, result);

    for (i = 0; i < n; i++)
    {
        printf("%.6lf\n", result[i]);
    }

    return 0;
}
