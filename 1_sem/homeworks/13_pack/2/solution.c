#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

double distance(double x1, double y1, double x2, double y2)
{
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

double get_cos_triangle(double Ax, double Ay,
                        double Bx, double By,
                        double Cx, double Cy)
{
    double AB = distance(Ax, Ay, Bx, By);
    double AC = distance(Ax, Ay, Cx, Cy);
    double BC = distance(Bx, By, Cx, Cy);

    double cos_angle = (AB * AB + AC * AC - BC * BC) / (2 * AB * AC);

    if (cos_angle > 1.0) cos_angle = 1.0;
    if (cos_angle < -1.0) cos_angle = -1.0;

    return cos_angle;
}

double factorial(int n)
{
    double result = 1;
    for (int i = 2; i <= n; i++)
    {
        result *= i;
    }
    return result;
}

double arcsin(double x)
{

    double result = 0.0;
    double term = x;
    int n = 0;

    for (n = 0; n < 10000; n++)
    {
        double numerator = factorial(2 * n);
        double denominator = pow(2, 2 * n) * pow(factorial(n), 2) * (2 * n + 1);
        term = numerator / denominator * pow(x, 2 * n + 1);
        result += term;
        if (term < 1e-20)
        {
            break;
        }
    }

    return result;
}

double arccos(double x)
{
    return PI / 2 - asin(x);;
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

        double cos_angle = get_cos_triangle(Ax, Ay, Bx, By, Cx, Cy);
        double angle_rad = arccos(cos_angle);
        double angle_deg = angle_rad * 180.0 / PI;

        printf("%0.20g\n", angle_deg);
    }

    return 0;
}
