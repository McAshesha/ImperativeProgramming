#include <stdio.h>
#include <stdlib.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2

typedef struct Edge {
    int dest;
    struct Edge* next;
} Edge;

typedef struct Graph {
    int n;
    Edge **adj;
    Edge **reverse_adj;
} Graph;

void add_edge(Graph* graph, int src, int dest) {
    Edge* new_edge = (Edge*)malloc(sizeof(Edge));
    new_edge->dest = dest;
    new_edge->next = graph->adj[src];
    graph->adj[src] = new_edge;

    Edge* new_reverse_edge = (Edge*)malloc(sizeof(Edge));
    new_reverse_edge->dest = src;
    new_reverse_edge->next = graph->reverse_adj[dest];
    graph->reverse_adj[dest] = new_reverse_edge;
}

void dfs_visit(Graph* graph, int u, int* visited, int* component, int component_number) {
    visited[u] = GRAY;
    component[u] = component_number;

    Edge* current = graph->adj[u];
    while (current != NULL) {
        int v = current->dest;
        if (visited[v] == WHITE) {
            dfs_visit(graph, v, visited, component, component_number);
        }
        current = current->next;
    }
}

void dfs_reverse(Graph* graph, int u, int* visited, int* stack, int* top) {
    visited[u] = GRAY;

    Edge* current = graph->reverse_adj[u];
    while (current != NULL) {
        int v = current->dest;
        if (visited[v] == WHITE) {
            dfs_reverse(graph, v, visited, stack, top);
        }
        current = current->next;
    }

    stack[++(*top)] = u;
}

void find_strongly_connected_components(Graph* graph) {
    int n = graph->n;
    int* visited = (int*)calloc(n, sizeof(int));
    int* stack = (int*)malloc(n * sizeof(int));
    int top = -1;

    for (int i = 0; i < n; ++i) {
        if (visited[i] == WHITE) {
            dfs_reverse(graph, i, visited, stack, &top);
        }
    }

    for (int i = 0; i < n; ++i) {
        visited[i] = WHITE;
    }

    int component_number = 0;
    int* component = (int*)malloc(n * sizeof(int));

    while (top != -1) {
        int u = stack[top--];
        if (visited[u] == WHITE) {
            dfs_visit(graph, u, visited, component, component_number++);
        }
    }

    printf("%d\n", component_number);
    for (int i = 0; i < n; ++i) {
        printf("%d ", component[i] + 1);
    }
    printf("\n");

    free(stack);
    free(visited);
    free(component);
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m;
    scanf("%d %d", &n, &m);

    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->n = n;
    graph->adj = (Edge**)calloc(n, sizeof(Edge*));
    graph->reverse_adj = (Edge**)calloc(n, sizeof(Edge*));

    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(graph, u - 1, v - 1);
    }

    find_strongly_connected_components(graph);

    for (int i = 0; i < n; ++i) {
        Edge* current = graph->adj[i];
        while (current != NULL) {
            Edge* temp = current;
            current = current->next;
            free(temp);
        }
        current = graph->reverse_adj[i];
        while (current != NULL) {
            Edge* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(graph->adj);
    free(graph->reverse_adj);
    free(graph);

    return 0;
}
