#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int merge(const int *a, int ak, const int *b, int bk, int *res)
{
    int i = 0, j = 0, k = 0;

    while (i < ak && j < bk)
    {
        if (a[i] <= b[j])
        {
            res[k++] = a[i++];
        }
        else
        {
            res[k++] = b[j++];
        }
    }

    while (i < ak)
    {
        res[k++] = a[i++];
    }

    while (j < bk)
    {
        res[k++] = b[j++];
    }

    return k;
}

int main() {
    FILE *in = fopen("input.txt", "rb");
    FILE *out = fopen("output.txt", "wb");

    int32_t N, M;
    fread(&N, sizeof(int32_t), 1, in);
    fread(&M, sizeof(int32_t), 1, in);

    int32_t *a = malloc(N * sizeof(int32_t));
    int32_t *b = malloc(M * sizeof(int32_t));

    fread(a, sizeof(int32_t), N, in);
    fread(b, sizeof(int32_t), M, in);

    int32_t *res = malloc((N + M) * sizeof(int32_t));
    int32_t rk = merge(a, N, b, M, res);

    fwrite(res, sizeof(int32_t), rk, out);

    free(a);
    free(b);
    free(res);

    fclose(in);
    fclose(out);

    return 0;
}
