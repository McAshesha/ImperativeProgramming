#include <stdio.h>

int main()
{
    FILE *in = fopen("binput.txt", "rb");
    FILE *out = fopen("boutput.txt", "wb");

    long a, b, ans;

    fread(&a, sizeof(long), 1, in);
    fread(&b, sizeof(long), 1, in);

    long long sum = (long long) a + (long long) b;
    ans = (long) (sum >> 1);

    fwrite(&ans, sizeof(long), 1, out);

    fclose(in);
    fclose(out);
    return 0;
}
