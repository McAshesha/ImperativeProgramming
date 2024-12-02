#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void swap(int32_t *a, int32_t *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int32_t partition(int32_t array[], int32_t low, int32_t high)
{
    int32_t pivot = array[high];
    int index = (low - 1);

    for (int j = low; j < high; j ++)
    {
        if (array[j] <= pivot)
        {
            swap(array + (++ index), array + j);
        }
    }

    swap(array + index + 1, array + high);
    return index + 1;
}

void sort(int32_t array[], int32_t low, int32_t high)
{
    if (low >= high)
        return;

    int32_t pivot = partition(array, low, high);
    sort(array, low, pivot - 1);
    sort(array, pivot + 1, high);
}


int main()
{
    FILE *fin = fopen("input.txt", "rb");
    FILE *fout = fopen("output.txt", "wb");

    int32_t N;

    fread(&N, sizeof(int32_t), 1, fin);

    int32_t *A = malloc(N * sizeof(int32_t));

    fread(A, sizeof(int32_t), N, fin);

    sort(A, 0, N - 1);

    fwrite(A, sizeof(int32_t), N, fout);

    free(A);

    fclose(fout);
    fclose(fin);

    return 0;
}
