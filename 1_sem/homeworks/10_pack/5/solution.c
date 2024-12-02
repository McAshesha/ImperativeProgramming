#include <stdio.h>

double calculate_sin(double x)
{
    double term = x;
    double sum = x;

    for (int n = 1; n < 1000; n++)
    {
        term *= -x * x / ((2 * n) * (2 * n + 1));
        if (term > -1e-12 && term < 1e-12)
        {
            break;
        }
        sum += term;
    }
    return sum;
}

int main()
{
    /* Redirect standard input to read from "input.txt" and output to "output.txt" */
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; i++)
    {
        double x;
        scanf("%lf", &x);
        printf("%0.15lf\n", calculate_sin(x));
    }

    fclose(stdin);
    fclose(stdout);

    return 0;
}
