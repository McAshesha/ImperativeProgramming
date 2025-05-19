#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 300
#define INF 1000000000000000000LL  // 1e18

int N, M, P, K;
long long dist[MAXN+1][MAXN+1];
int nxt[MAXN+1][MAXN+1];

int main() {
    scanf("%d %d %d %d", &N, &M, &P, &K);

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (i == j) {
                dist[i][j] = 0;
            } else {
                dist[i][j] = INF;
            }
            nxt[i][j] = -1;
        }
    }

    for (int e = 0; e < M; e++) {
        int u, v;
        long long w;
        scanf("%d %d %lld", &u, &v, &w);
        if (w < dist[u][v]) {
            dist[u][v] = dist[v][u] = w;
            nxt[u][v] = v;
            nxt[v][u] = u;
        }
    }

    for (int k = 1; k <= N; k++) {
        for (int i = 1; i <= N; i++) {
            if (dist[i][k] == INF) continue;
            for (int j = 1; j <= N; j++) {
                long long through = dist[i][k] + dist[k][j];
                if (through < dist[i][j]) {
                    dist[i][j] = through;
                    nxt[i][j] = nxt[i][k];
                }
            }
        }
    }

    int *qs_u = malloc((P+K) * sizeof(int));
    int *qs_v = malloc((P+K) * sizeof(int));

    for (int i = 0; i < P + K; i++) {
        scanf("%d %d", &qs_u[i], &qs_v[i]);
    }

    for (int q = 0; q < P; q++) {
        int u = qs_u[q], v = qs_v[q];
        long long d = dist[u][v];
        int path[MAXN+1];
        int path_len = 0;
        if (nxt[u][v] == -1) {
            path_len = 0;
        } else {
            int cur = u;
            while (cur != v) {
                path[path_len++] = cur;
                cur = nxt[cur][v];
            }
            path[path_len++] = v;
        }
        printf("%lld %d", d, path_len);
        for (int i = 0; i < path_len; i++) {
            printf(" %d", path[i]);
        }
        printf("\n");
    }

    for (int q = P; q < P+K; q++) {
        int u = qs_u[q], v = qs_v[q];
        printf("%lld\n", dist[u][v]);
    }

    free(qs_u);
    free(qs_v);
    return 0;
}
