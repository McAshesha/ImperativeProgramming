#include <stdio.h>
#include <stdlib.h>

void compute(int n, int **matrix)
{
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (matrix[i][k] && matrix[k][j])
                {
                    matrix[i][j] = 1;
                }
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        matrix[i][i] = 1;
    }
}

int main()
{
    int n;

    scanf("%d", &n);
    int **matrix = (int **) malloc(sizeof(int *) * n);

    for (int i = 0; i < n; i++)
    {
        matrix[i] = (int *) malloc(sizeof(int) * n);
        for (int j = 0; j < n; j++)
        {
            scanf(" %1d", &matrix[i][j]);
        }
    }

    compute(n, matrix);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}
