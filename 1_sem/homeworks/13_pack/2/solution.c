#include <stdio.h>
#include <math.h>

#define PI 3.141592653589793
#define EPSILON 1e-20

double get_tan_triangle(double Ax, double Ay,
                        double Bx, double By,
                        double Cx, double Cy)
{
    return fabs((Bx - Ax) * (Cy - Ay) - (Cx - Ax) * (By - Ay))
            / ((Bx - Ax) * (Cx - Ax) + (By - Ay) * (Cy - Ay));
}

double arctan(double x)
{
    if (x > 1.0)
    {
        return PI / 2 - arctan(1.0 / x);
    }
    if (x < -1.0)
    {
        return -PI / 2 - arctan(1.0 / x);
    }
    if (fabs(x) > 0.5)
    {
        return 2 * arctan(x / (1.0 + sqrt(1.0 + x * x)));
    }

    double term = x;
    double sum = x;
    double x_squared_neg = -x * x;
    int n = 1;

    while (fabs(term) >= EPSILON)
    {
        term *= x_squared_neg * (2 * n - 1) / (2 * n + 1);
        sum += term;
        n++;
    }

    return sum < 0 ? PI + sum : sum;
}

int main()
{
    /* Redirect standard input to read from "input.txt" and output to "output.txt" */
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int Q;
    scanf("%d", &Q);

    while (Q--)
    {
        double Ax, Ay, Bx, By, Cx, Cy;
        scanf("%lf %lf %lf %lf %lf %lf", &Ax, &Ay, &Bx, &By, &Cx, &Cy);

        double cos_angle = get_tan_triangle(Ax, Ay, Bx, By, Cx, Cy);
        double angle_rad = arctan(cos_angle);
        double angle_deg = angle_rad * 180.0 / PI;

        printf("%0.20g\n", angle_deg);
    }

    return 0;
}
