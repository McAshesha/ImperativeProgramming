#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 3005
#define MAXM 600005
#define MAXK 25

typedef long long ll;

typedef struct {
    int to, w, next;
} Edge;

Edge edges[MAXM];
int head[MAXN], edgeCnt = 0;

void addEdge(int u, int v, int w) {
    edges[edgeCnt].to   = v;
    edges[edgeCnt].w    = w;
    edges[edgeCnt].next = head[u];
    head[u] = edgeCnt++;
}

const ll INF = (ll)1e18;

typedef struct {
    int u;
    ll dist;
} HeapNode;

HeapNode heap[MAXM];
int heap_size = 0;

void heap_swap(int i, int j) {
    HeapNode t = heap[i];
    heap[i] = heap[j];
    heap[j] = t;
}

void heap_push(int u, ll d) {
    int i = ++heap_size;
    heap[i].u    = u;
    heap[i].dist = d;
    while (i > 1) {
        int p = i >> 1;
        if (heap[p].dist <= heap[i].dist) break;
        heap_swap(p, i);
        i = p;
    }
}

HeapNode heap_pop() {
    HeapNode ret = heap[1];
    heap[1] = heap[heap_size--];
    int i = 1;
    while (1) {
        int l = i << 1, r = l + 1, m = i;
        if (l <= heap_size && heap[l].dist < heap[m].dist) m = l;
        if (r <= heap_size && heap[r].dist < heap[m].dist) m = r;
        if (m == i) break;
        heap_swap(i, m);
        i = m;
    }
    return ret;
}

int N, M, K;
int queries[MAXK][2];
ll distArr[MAXN];
int parentArr[MAXN];

int main() {
    scanf("%d %d %d", &N, &M, &K);
    for (int i = 1; i <= N; ++i) head[i] = -1;

    for (int i = 0; i < K; ++i) {
        scanf("%d %d", &queries[i][0], &queries[i][1]);
    }
    for (int i = 0, u, v, w; i < M; ++i) {
        scanf("%d %d %d", &u, &v, &w);
        addEdge(u, v, w);
        addEdge(v, u, w);
    }

    for (int qi = 0; qi < K; ++qi) {
        int S = queries[qi][0];
        int T = queries[qi][1];

        for (int i = 1; i <= N; ++i) {
            distArr[i]   = INF;
            parentArr[i] = 0;
        }
        distArr[S] = 0;
        heap_size = 0;
        heap_push(S, 0);

        while (heap_size > 0) {
            HeapNode hn = heap_pop();
            int u = hn.u;
            ll d = hn.dist;
            if (d != distArr[u]) continue;
            if (u == T) break;
            for (int e = head[u]; e != -1; e = edges[e].next) {
                int v = edges[e].to;
                ll nd = d + edges[e].w;
                if (nd < distArr[v]) {
                    distArr[v]   = nd;
                    parentArr[v] = u;
                    heap_push(v, nd);
                }
            }
        }

        if (distArr[T] == INF) {
            printf("NO\n");
        } else {
            int path[MAXN], cnt = 0;
            for (int cur = T; cur != 0; cur = parentArr[cur]) {
                path[cnt++] = cur;
            }
            for (int i = 0; i < cnt/2; ++i) {
                int t = path[i];
                path[i] = path[cnt-1-i];
                path[cnt-1-i] = t;
            }
            printf("YES %lld %d", distArr[T], cnt);
            for (int i = 0; i < cnt; ++i) {
                printf(" %d", path[i]);
            }
            printf("\n");
        }
    }

    return 0;
}
