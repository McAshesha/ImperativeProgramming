#include <stdio.h>

#define EXP 1e-15

extern double Function(double x);

double Derivative(double x)
{
    return (Function(x) - Function(x - EXP)) / EXP;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int M;
    scanf("%d", &M);

    for (int i = 0; i < M; i++)
    {
        double x;
        scanf("%lf", &x);
        double derivative = Derivative(x);
        printf("%.10lf\n", derivative);
    }

    return 0;
}