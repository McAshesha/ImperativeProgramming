#include <stdio.h>
#define MAX_N 1500

double pascal_triangle[MAX_N + 1][MAX_N + 1];

void build_pascal_triangle() {
    for (int i = 0; i < MAX_N; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            if (j == 0 || j == i)
            {
                pascal_triangle[i][j] = 1;
            }
            else
            {
                pascal_triangle[i][j] = pascal_triangle[i - 1][j - 1] + pascal_triangle[i - 1][j];
            }
        }
    }
}

int main()
{
    /* Redirect standard input to read from "input.txt" and standard output to "output.txt" */
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int Q, n, k;

    build_pascal_triangle();

    scanf("%d", &Q);

    for (int i = 0; i < Q; i++) {
        scanf("%d %d", &n, &k);
        printf("%0.10g\n", pascal_triangle[n][k]);
    }

    /* Close the file streams for input and output */
    fclose(stdin);
    fclose(stdout);

    return 0;  // Exit the program
}
