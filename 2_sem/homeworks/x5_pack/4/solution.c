#include <stdio.h>
#include <stdlib.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2

int *assigned_values;
char *visited;
int *in_degrees;
int n, m;

typedef struct Edge {
    int dest;
    struct Edge *next;
} Edge;

Edge **adj;

void add_edge(int src, int dest) {
    Edge *new_edge = (Edge *) malloc(sizeof(Edge));
    new_edge->dest = dest;
    new_edge->next = adj[src];
    adj[src] = new_edge;
}

int topological_sort() {
    int *stack = (int *) malloc(n * sizeof(int));
    int top = -1;

    for (int i = 0; i < n; ++i) {
        if (in_degrees[i] == 0) {
            stack[++top] = i;
        }
    }

    int count = 0;

    while (top != -1) {
        int u = stack[top--];
        assigned_values[u] = ++count;

        Edge *current = adj[u];
        while (current != NULL) {
            int v = current->dest;
            --in_degrees[v];
            if (in_degrees[v] == 0) {
                stack[++top] = v;
            }
            current = current->next;
        }
    }

    free(stack);

    return count == n;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    scanf("%d %d", &n, &m);

    assigned_values = (int *) malloc(n * sizeof(int));
    visited = (char *) calloc(n, sizeof(char));
    in_degrees = (int *) calloc(n, sizeof(int));
    adj = (Edge **) calloc(n, sizeof(Edge *));

    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u - 1, v - 1);
        ++in_degrees[v - 1];
    }

    if (!topological_sort()) {
        printf("NO\n");
        return 0;
    }

    printf("YES\n");
    for (int i = 0; i < n; ++i) {
        printf("%d ", assigned_values[i]);
    }

    free(assigned_values);
    free(visited);
    free(in_degrees);
    for (int i = 0; i < n; ++i) {
        Edge *current = adj[i];
        while (current != NULL) {
            Edge *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(adj);

    return 0;
}
