#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 10
#define MAXK 10
#define MAXM 100

int N, K, M, L;
int effect[MAXN][MAXK][MAXM];
int cur[MAXM];
int sol[MAXN];

void dfs(int idx) {
    if (idx == N) {
        for (int t = 0; t < M; t++) {
            if (cur[t] != L) return;
        }
        printf("YES\n");
        for (int i = 0; i < N; i++) {
            printf("%d\n", sol[i] + 1);
        }
        exit(0);
    }

    int rem = N - idx - 1;
    for (int j = 0; j < K; j++) {
        int ok = 1;
        for (int t = 0; t < M; t++) {
            cur[t] += effect[idx][j][t];
            if (cur[t] > L) ok = 0;
        }
        if (!ok) {
            for (int t = 0; t < M; t++) {
                cur[t] -= effect[idx][j][t];
            }
            continue;
        }
        for (int t = 0; t < M; t++) {
            if (cur[t] + rem < L) {
                ok = 0;
                break;
            }
        }
        if (ok) {
            sol[idx] = j;
            dfs(idx + 1);
        }
        for (int t = 0; t < M; t++) {
            cur[t] -= effect[idx][j][t];
        }
    }
}

int main() {
    scanf("%d %d %d %d", &N, &K, &M, &L);

    char line[MAXM + 5];
    int count = 0;
    while (count < N * K && fgets(line, sizeof(line), stdin)) {
        if (strchr(line, 'X') == NULL && strchr(line, '.') == NULL) {
            continue;
        }
        int len = strlen(line);
        while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r')) {
            line[--len] = '\0';
        }
        if (len < M) {
            continue;
        }
        int i = count / K;
        int j = count % K;
        for (int t = 0; t < M; t++) {
            effect[i][j][t] = (line[t] == 'X') ? 1 : 0;
        }
        count++;
    }

    for (int t = 0; t < M; t++) cur[t] = 0;

    dfs(0);

    printf("NO\n");
    return 0;
}
