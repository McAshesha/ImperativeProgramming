#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int partition(int *a, int n, int pivot)
{
    int c_less = 0, c_equal = 0, c_greater = 0;

    // Первый проход: подсчет количества элементов
    for (int i = 0; i < n; i++)
    {
        if (a[i] < pivot)
        {
            c_less++;
        }
        else if (a[i] == pivot)
        {
            c_equal++;
        }
        else
        {
            c_greater++;
        }
    }

    // Распределение элементов, равных pivot
    int u = c_equal / 2;
    int v = c_equal - u;
    int k = c_less + u;

    // Выделение памяти для временных массивов
    int *less = malloc(c_less * sizeof(int));
    int *equal = malloc(c_equal * sizeof(int));
    int *greater = malloc(c_greater * sizeof(int));


    // Второй проход: заполнение временных массивов
    for (int idx_less = 0, idx_equal = 0, idx_greater = 0, i = 0; i < n; i++)
    {
        if (a[i] < pivot)
        {
            less[idx_less++] = a[i];
        }
        else if (a[i] == pivot)
        {
            equal[idx_equal++] = a[i];
        }
        else
        {
            greater[idx_greater++] = a[i];
        }
    }

    int idx = 0;

    // Перенос элементов обратно в массив a
    for (int i = 0; i < c_less; i++)
    {
        a[idx++] = less[i];
    }

    for (int i = 0; i < u + v; i++)
    {
        a[idx++] = equal[i];
    }

    for (int i = 0; i < c_greater; i++)
    {
        a[idx++] = greater[i];
    }

    free(less);
    free(equal);
    free(greater);

    return k;
}

int main()
{
    FILE *in = fopen("input.txt", "rb");
    FILE *out = fopen("output.txt", "wb");

    int32_t N, pivot;

    fread(&N, sizeof(int32_t), 1, in);
    fread(&pivot, sizeof(int32_t), 1, in);

    int32_t *a = malloc(N * sizeof(int32_t));

    fread(a, sizeof(int32_t), N, in);

    int k = partition((int *)a, N, pivot);

    fwrite(&k, sizeof(int32_t), 1, out);
    fwrite(a, sizeof(int32_t), N, out);

    fclose(out);
    fclose(in);
    free(a);

    return 0;
}
