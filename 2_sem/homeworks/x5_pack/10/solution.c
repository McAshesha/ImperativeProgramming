#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 100005       // maximum number of vertices
#define MAXM 100005       // maximum number of edges
#define MAXE (2*MAXM)     // maximum number of adjacency entries

int N, M;
int head[MAXN];           // head[u] = index of first edge from u
int to[MAXE];             // to[e] = endpoint vertex of adjacency entry e
int nxt[MAXE];            // nxt[e] = next adjacency entry index from same u
int eid[MAXE];            // eid[e] = original input edge index for adjacency entry e

bool isBridge[MAXM];      // isBridge[i] = true if edge i is a bridge
int disc[MAXN], low[MAXN], vis[MAXN];
int timer = 0;
int edgeCnt = 0;

// add an undirected adjacency entry for edge id between u -> v
void addEdge(int u, int v, int id) {
    to[edgeCnt] = v;
    eid[edgeCnt] = id;
    nxt[edgeCnt] = head[u];
    head[u] = edgeCnt++;
}

// Tarjan's DFS to compute discovery times and low-link values
void dfs(int u, int parentEdgeId) {
    vis[u] = 1;
    disc[u] = low[u] = ++timer;
    for (int e = head[u]; e != -1; e = nxt[e]) {
        int v = to[e];
        int id = eid[e];
        if (!vis[v]) {
            dfs(v, id);
            // propagate low-link value from child
            if (low[v] < low[u]) low[u] = low[v];
            // if no back-edge from v or its descendants to u or ancestors, it's a bridge
            if (low[v] > disc[u]) {
                isBridge[id] = true;
            }
        } else if (id != parentEdgeId) {
            // back-edge (not the one we came from)
            if (disc[v] < low[u]) low[u] = disc[v];
        }
    }
}

int main() {
    // read number of vertices and edges
    if (scanf("%d %d", &N, &M) != 2) return 0;

    // initialize adjacency heads
    for (int i = 1; i <= N; i++) {
        head[i] = -1;
    }

    // read edges and build graph
    for (int i = 1; i <= M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(u, v, i);
        addEdge(v, u, i);
    }

    // run DFS from every unvisited vertex (to cover all components)
    for (int i = 1; i <= N; i++) {
        if (!vis[i]) {
            dfs(i, -1);
        }
    }

    // collect and print bridges
    int count = 0;
    for (int i = 1; i <= M; i++) {
        if (isBridge[i]) count++;
    }

    printf("%d\n", count);
    bool first = true;
    for (int i = 1; i <= M; i++) {
        if (isBridge[i]) {
            if (!first) printf(" ");
            printf("%d", i);
            first = false;
        }
    }
    printf("\n");

    return 0;
}
