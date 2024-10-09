#include <stdio.h>


int main(void)
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N;
    scanf("%d", &N);

    for (int _ = 0; _ < N; _++)
    {
        int h, m, s;
        scanf("%d %d %d", &h, &m, &s);
        printf("%02d:%02d:%02d\n", h, m, s);
    }

    fclose(stdin);
    fclose(stdout);

    return 0;
}
