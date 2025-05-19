#include <stdio.h>

#define MOD 1000000007

int memo[1001][1001];

int rec(int Sum, int Last, int N) {
    if (memo[Sum][Last] == -1) {
        int res = 0;
        if (Sum == N) {
            res = 1;
        } else {
            for (int x = 1; x <= Last && Sum + x <= N; x++) {
                res = (res + rec(Sum + x, x, N)) % MOD;
            }
        }
        memo[Sum][Last] = res;
    }
    return memo[Sum][Last];
}

int main() {
    int N;
    scanf("%d", &N);

    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= N; j++) {
            memo[i][j] = -1;
        }
    }

    printf("%d\n", rec(0, N, N));

    return 0;
}
