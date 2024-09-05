#include <stdio.h>


int main(void)
{
    int N;

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    scanf("%d", &N);

    int count_positive = 0, count_negative = 0, count_neutral = 0;

    for (int i = 0; i < N; i++)
    {
        int element;
        scanf("%d", &element);

        if (element > 0)
        {
            count_positive++;
        }
        else if (element < 0)
        {
            count_negative++;
        }
        else {
            count_neutral ++;
        }
    }

    printf("%.5lf %.5lf %.5lf", (double) count_negative / N, (double) count_neutral / N, (double) count_positive / N);

    fclose(stdin);
    fclose(stdout);

    return 0; // Indicate successful program termination
}
