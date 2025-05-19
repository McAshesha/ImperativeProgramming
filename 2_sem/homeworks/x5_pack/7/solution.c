#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

#define INFLL (LLONG_MAX/4)

typedef struct {
    int u, v;
    int w;
} Edge;

int main() {
    int N, M, K;
    scanf("%d %d %d", &N, &M, &K);

    int *friends = malloc(K * sizeof(int));
    for (int i = 0; i < K; i++) {
        scanf("%d", &friends[i]);
    }

    Edge *edges = malloc(M * sizeof(Edge));
    for (int i = 0; i < M; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }

    long long *dist = malloc((N + 1) * sizeof(long long));
    int *pred = malloc((N + 1) * sizeof(int));

    for (int v = 1; v <= N; v++) {
        dist[v] = INFLL;
        pred[v] = 0;
    }
    dist[1] = 0;

    for (int it = 1; it < N; it++) {
        int updated = 0;
        for (int i = 0; i < M; i++) {
            int u = edges[i].u;
            int v = edges[i].v;
            int w = edges[i].w;
            if (dist[u] != INFLL && dist[u] + (long long)w < dist[v]) {
                dist[v] = dist[u] + (long long)w;
                pred[v] = u;
                updated = 1;
            }
        }
        if (!updated) break;
    }

    for (int i = 0; i < K; i++) {
        int t = friends[i];
        long long d = dist[t];

        int *path = malloc((N + 1) * sizeof(int));
        int len = 0;
        for (int cur = t; cur != 0; cur = pred[cur]) {
            path[len++] = cur;
        }

        printf("%lld %d", d, len);
        for (int j = len - 1; j >= 0; j--) {
            printf(" %d", path[j]);
        }
        printf("\n");
        free(path);
    }

    free(friends);
    free(edges);
    free(dist);
    free(pred);
    return 0;
}
