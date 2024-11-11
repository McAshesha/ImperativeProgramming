#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void merge(int32_t *a, int32_t *tmp, int left, int mid, int right)
{
    int i = left, j = mid, k = left;
    while (i < mid && j < right)
    {
        if (a[i] <= a[j])
        {
            tmp[k++] = a[i++];
        }
        else
        {
            tmp[k++] = a[j++];
        }
    }

    while (i < mid)
    {
        tmp[k++] = a[i++];
    }
    while (j < right)
    {
        tmp[k++] = a[j++];
    }

    for (i = left; i < right; i++)
    {
        a[i] = tmp[i];
    }
}

void merge_sort(int32_t *a, int32_t *tmp, int left, int right)
{
    if (right - left <= 1)
    {
        return;
    }

    int mid = (right + left) / 2;

    merge_sort(a, tmp, left, mid);
    merge_sort(a, tmp, mid, right);

    merge(a, tmp, left, mid, right);
}

int main()
{
    FILE *in = fopen("input.txt", "rb");
    FILE *out = fopen("output.txt", "wb");

    int32_t N;

    fread(&N, sizeof(int32_t), 1, in);

    int32_t *A = malloc(N * sizeof(int32_t));
    int32_t *tmp = malloc(N * sizeof(int32_t));

    fread(A, sizeof(int32_t), N, in);

    merge_sort(A, tmp, 0, N);

    free(tmp);

    fwrite(A, sizeof(int32_t), N, out);

    free(A);

    fclose(out);
    fclose(in);

    return 0;
}
