#include <stdio.h>
#include <stdlib.h>

long long bin_pow(long long a, long long exp, int mod) {
    long long res = 1;
    a %= mod;
    while (exp > 0) {
        if (exp & 1) {
            res = (res * a) % mod;
        }
        a = (a * a) % mod;
        exp >>= 1;
    }
    return res;
}

long long reciprocal(int A, int M) {
    if (M <= 1) {
        return -1;
    }
    A %= M;
    if (A == 0) {
        return -1;
    }
    long long B = bin_pow(A, M - 2, M);
    return (A * B) % M == 1 ? B : -1;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int T, M;
    scanf("%d %d", &T, &M);

    while (T--) {
        int A;
        scanf("%d", &A);
        printf("%lld\n", reciprocal(A, M));
    }

    return 0;
}