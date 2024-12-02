#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void swap(int32_t* a, int32_t* b)
{
    int32_t temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int32_t arr[], uint32_t n, uint32_t i)
{
    uint32_t largest = i;
    uint32_t left = 2 * i + 1;
    uint32_t right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
    {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest])
    {
        largest = right;
    }

    if (largest != i)
    {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int32_t arr[], uint32_t n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i > 0; i--)
    {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

int main()
{
    FILE *fin = fopen("input.bin", "rb");
    FILE *fout = fopen("output.bin", "wb");

    uint32_t N;
    fread(&N, sizeof(uint32_t), 1, fin);

    int32_t* A = malloc(N * sizeof(int32_t));
    fread(A, sizeof(int32_t), N, fin);

    heapSort(A, N);

    fwrite(A, sizeof(int32_t), N, fout);

    free(A);
    fclose(fin);
    fclose(fout);

    return 0;
}
