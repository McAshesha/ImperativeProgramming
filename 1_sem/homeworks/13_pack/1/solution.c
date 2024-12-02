#include <stdio.h>

double myExp(double x)
{
    if (x < 0) {
        return 1.0 / myExp(-x);
    }
    double result = 1.0;
    double term = 1.0;

    for (int n = 1; n < 1000; n++)
    {
        term *= x / n;
        result += term;

        if (term < 1e-15)
        {
            break;
        }
    }

    return result;
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
        double X;
        scanf("%lf", &X);

        double result = myExp(X);
        printf("%0.15g\n", result);
    }

    return 0;
}
