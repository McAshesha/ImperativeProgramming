#include <stdio.h>
#include <math.h>


int canFit(int a_1, int a_2, int b_1, int b_2, int c_1, int c_2)
{
    if ((b_1 + c_1 <= a_1 && b_2 <= a_2 && c_2 <= a_2) || (b_2 + c_2 <= a_2 && b_1 <= a_1 && c_1 <= a_1))
    {
        return 1;
    }

    if ((b_1 <= a_1 && c_1 <= a_1 && b_2 + c_2 <= a_2) || (b_2 <= a_2 && c_2 <= a_2 && b_1 + c_1 <= a_1))
    {
        return 1;
    }

    return 0;
}


int main(void)
{
    int a_1, a_2;
    int b_1, b_2;
    int c_1, c_2;

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    scanf("%d %d", &a_1, &a_2);
    scanf("%d %d", &b_1, &b_2);
    scanf("%d %d", &c_1, &c_2);

    if (b_1 * b_2 + c_1 * c_2 > a_1 * a_2)
    {
        printf("NO\n");
        return 0;
    }

    // Проверка всех возможных поворотов прямоугольников B и C
    if (canFit(a_1, a_2, b_1, b_2, c_1, c_2) ||  // Обычные ориентации
        canFit(a_1, a_2, b_1, b_2, c_2, c_1) ||  // C повернут на 90 градусов
        canFit(a_1, a_2, b_2, b_1, c_1, c_2) ||  // B повернут на 90 градусов
        canFit(a_1, a_2, b_2, b_1, c_2, c_1)) // Оба повернуты на 90 градусов
    {
        printf("YES\n");
    }
    else {
        printf("NO\n");
    }


    fclose(stdin);
    fclose(stdout);

    return 0; // Indicate successful program termination
}
