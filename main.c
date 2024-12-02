#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

double distance(double x1, double y1, double x2, double y2)
{
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

int main()
{
    int Q;
    scanf("%d", &Q);

    while (Q--)
    {
        double Ax, Ay, Bx, By, Cx, Cy;
        scanf("%lf %lf %lf %lf %lf %lf", &Ax, &Ay, &Bx, &By, &Cx, &Cy);

        double AB = distance(Ax, Ay, Bx, By);
        double AC = distance(Ax, Ay, Cx, Cy);
        double BC = distance(Bx, By, Cx, Cy);

        double cos_angle = (AB * AB + AC * AC - BC * BC) / (2 * AB * AC);

        if (cos_angle > 1.0) cos_angle = 1.0;
        if (cos_angle < -1.0) cos_angle = -1.0;

        // Вычисляем угол в радианах
        double angle_rad = acos(cos_angle);

        // Переводим угол в градусы
        double angle_deg = angle_rad * 180.0 / PI;

        // Выводим угол с точностью
        printf("%0.20g\n", angle_deg);
    }

    return 0;
}
