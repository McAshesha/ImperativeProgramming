#include <stdio.h>

#define MAXN 200
#define MAXW 50000
#define MAXC 1000000

int N, Wmax;
int w[MAXN], c[MAXN];
int memo[MAXN][MAXW + 1];
int F[MAXN][MAXW + 1];

int max(int a, int b) {
    return (a > b) ? a : b;
}

int rec(int k, int sumW) {
    if (k == N)
        return 0;
    if (memo[k][sumW] != -1)
        return memo[k][sumW];

    int Cskip = rec(k + 1, sumW);
    int Ctake = 0;
    if (sumW + w[k] <= Wmax)
        Ctake = rec(k + 1, sumW + w[k]) + c[k];

    if (Ctake > Cskip) {
        F[k][sumW] = 1; // take
        memo[k][sumW] = Ctake;
    } else {
        F[k][sumW] = 0; // skip
        memo[k][sumW] = Cskip;
    }

    return memo[k][sumW];
}

void restore_solution() {
    int sumW = 0;
    for (int k = 0; k < N; k++) {
        if (F[k][sumW] == 1) {
            printf("%d ", k + 1);
            sumW += w[k];
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    scanf("%d %d", &N, &Wmax);

    for (int i = 0; i < N; i++) {
        scanf("%d %d", &w[i], &c[i]);
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= Wmax; j++) {
            memo[i][j] = -1;
            F[i][j] = -1;
        }
    }

    int optimal_cost = rec(0, 0);

    int sumW = 0;
    int K = 0;
    for (int k = 0; k < N; k++) {
        if (F[k][sumW] == 1) {
            sumW += w[k];
            K++;
        }
    }

    printf("%d %d %d\n", K, sumW, optimal_cost);
    restore_solution();

    return 0;
}
