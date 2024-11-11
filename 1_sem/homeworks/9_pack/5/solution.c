#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int compare(const void *a, const void *b)
{
    return *(int32_t *) a - *(int32_t *) b;
}

int main()
{
    FILE *fin = fopen("input.txt", "rb");
    FILE *fout = fopen("output.txt", "wb");

    int32_t N;

    fread(&N, sizeof(int32_t), 1, fin);

    int32_t *A = malloc(N * sizeof(int32_t));

    fread(A, sizeof(int32_t), N, fin);

    qsort(A, N, sizeof(int32_t), compare);

    fwrite(A, sizeof(int32_t), N, fout);

    free(A);

    fclose(fout);
    fclose(fin);

    return 0;
}
