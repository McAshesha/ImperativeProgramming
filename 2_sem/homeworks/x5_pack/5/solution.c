#include <stdio.h>
#include <stdlib.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2

int *visited;
int *in_stack;
int *parent;
int n, m;
int cycle_start, cycle_end;
int *cycle;
int cycle_size;

typedef struct Edge {
    int dest;
    struct Edge* next;
} Edge;

Edge **adj;

void add_edge(int src, int dest) {
    Edge* new_edge = (Edge*)malloc(sizeof(Edge));
    new_edge->dest = dest;
    new_edge->next = adj[src];
    adj[src] = new_edge;
}

int dfs(int u, int parent_vertex) {
    visited[u] = GRAY;
    in_stack[u] = 1;
    parent[u] = parent_vertex;

    Edge* current = adj[u];
    while (current != NULL) {
        int v = current->dest;
        if (visited[v] == WHITE) {
            if (dfs(v, u))
                return 1;
        } else if (visited[v] == GRAY && v != parent[u]) {
            cycle_start = v;
            cycle_end = u;

            cycle = (int*)malloc(n * sizeof(int));
            cycle_size = 0;
            int vertex = u;

            while (vertex != v) {
                cycle[cycle_size++] = vertex;
                vertex = parent[vertex];
            }
            cycle[cycle_size++] = v;

            for (int i = 0; i < cycle_size / 2; ++i) {
                int temp = cycle[i];
                cycle[i] = cycle[cycle_size - i - 1];
                cycle[cycle_size - i - 1] = temp;
            }

            return 1;
        } else if (visited[v] == GRAY && v == parent[u]) {
            cycle_start = u;
            cycle_end = v;

            cycle = (int*)malloc(2 * sizeof(int));
            cycle_size = 2;
            cycle[0] = u;
            cycle[1] = v;

            return 1;
        }
        current = current->next;
    }

    visited[u] = BLACK;
    in_stack[u] = 0;
    return 0;
}


int find_cycle() {
    visited = (int*)calloc(n, sizeof(int));
    in_stack = (int*)calloc(n, sizeof(int));
    parent = (int*)malloc(n * sizeof(int));
    cycle_start = -1;

    for (int i = 0; i < n; ++i) {
        if (visited[i] == WHITE && dfs(i, -1))
            return 1;
    }

    return 0;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    scanf("%d %d", &n, &m);

    visited = (int*)calloc(n, sizeof(int));
    adj = (Edge**)calloc(n, sizeof(Edge*));

    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u - 1, v - 1);
    }

    if (find_cycle()) {
        if (cycle_size == 2) {
            printf("2\n%d %d\n", cycle[0] + 1, cycle[1] + 1);
        } else {
            printf("%d\n", cycle_size);
            for (int i = 0; i < cycle_size; ++i) {
                printf("%d ", cycle[i] + 1);
            }
            printf("\n");
        }
    } else {
        printf("-1\n");
    }

    free(visited);
    free(in_stack);
    free(parent);
    for (int i = 0; i < n; ++i) {
        Edge* current = adj[i];
        while (current != NULL) {
            Edge* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(adj);
    free(cycle);

    return 0;
}

