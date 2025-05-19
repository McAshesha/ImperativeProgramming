#include <stdio.h>
#include <math.h>

double calculate_polynomial(double c0, double c1, double c2, double c3, double t, double l)
{
    return c0 + c1 * (t - l) + c2 * pow(t - l, 2) + c3 * pow(t - l, 3);
}

double calculate_derivative(double c1, double c2, double c3, double t, double l)
{
    return c1 + 2 * c2 * (t - l) + 3 * c3 * pow(t - l, 2);
}

double calculate_span_length(double c1_x, double c2_x, double c3_x, double c1_y, double c2_y, double c3_y, double c1_z, double c2_z, double c3_z, double l, double r)
{
    double h = (r - l) / 1000;
    double sum = 0.0;

    for (int i = 0; i <= 1000; i++)
    {
        double t = l + i * h;

        double dx_dt = calculate_derivative(c1_x, c2_x, c3_x, t, l);
        double dy_dt = calculate_derivative(c1_y, c2_y, c3_y, t, l);
        double dz_dt = calculate_derivative(c1_z, c2_z, c3_z, t, l);

        if (i == 0 || i == 1000)
        {
            sum += sqrt(dx_dt * dx_dt + dy_dt * dy_dt + dz_dt * dz_dt);
        }
        else if (i % 2 == 1)
        {
            sum += 4 * sqrt(dx_dt * dx_dt + dy_dt * dy_dt + dz_dt * dz_dt);
        }
        else
        {
            sum += 2 * sqrt(dx_dt * dx_dt + dy_dt * dy_dt + dz_dt * dz_dt);
        }
    }

    sum *= h / 3;

    return sum;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N;
    scanf("%d", &N);

    double total_length = 0.0;

    for (int i = 0; i < N; i++)
    {
        double l, r;
        scanf("%lf %lf", &l, &r);

        double c0_x, c1_x, c2_x, c3_x;
        scanf("%lf %lf %lf %lf", &c0_x, &c1_x, &c2_x, &c3_x);

        double c0_y, c1_y, c2_y, c3_y;
        scanf("%lf %lf %lf %lf", &c0_y, &c1_y, &c2_y, &c3_y);

        double c0_z, c1_z, c2_z, c3_z;
        scanf("%lf %lf %lf %lf", &c0_z, &c1_z, &c2_z, &c3_z);

        double span_length = calculate_span_length(c1_x, c2_x, c3_x, c1_y, c2_y, c3_y, c1_z, c2_z, c3_z, l, r);
        total_length += span_length;
    }

    printf("%.15lf\n", total_length);
    return 0;
}
