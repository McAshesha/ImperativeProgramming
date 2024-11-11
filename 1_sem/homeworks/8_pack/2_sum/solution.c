#include <stdio.h>

int switch_endian(int number)
{
    return ((number & 0xFF) << 24) |
            (((number >> 8) & 0xFF) << 16) |
            (((number >> 16) & 0xFF) << 8) |
            ((number >> 24) & 0xFF);
}

int main()
{
    FILE *in = fopen("binput.txt", "rb");
    FILE *out = fopen("boutput.txt", "wb");

    int N, sum = 0;
    fread(&N, sizeof(int), 1, in);

    int is_big_endian = (N & 0xFFFF) == 0;
    if (is_big_endian)
    {
        N = switch_endian(N);
    }

    for (int i = 0; i < N; i++)
    {
        int num;
        fread(&num, sizeof(int), 1, in);
        if (is_big_endian)
        {
            num = switch_endian(num);
        }
        sum += num;
    }

    if (is_big_endian)
    {
        sum = switch_endian(sum);
    }
    fwrite(&sum, sizeof(int), 1, out);

    fclose(in);
    fclose(out);

    return 0;
}
