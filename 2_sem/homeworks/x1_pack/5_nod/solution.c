#include <stdio.h>

int gcd(int A, int B)
{
    return A == 0 ? B : gcd(B % A, A);
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int T;
    scanf("%d", &T);

    while (T--)
    {
        int A, B;
        scanf("%d %d", &A, &B);

        int result = gcd(A, B);
        printf("%d\n", result);
    }
    return 0;
}
