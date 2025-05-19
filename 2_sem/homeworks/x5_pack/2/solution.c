#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 200001
#define MAX_EDGES 200001

typedef struct {
    int vertex;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} LinkedList;

typedef struct {
    int vertices;
    LinkedList* array;
} Graph;

Node* createNode(int vertex) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->vertices = vertices;
    graph->array = (LinkedList*)malloc(vertices * sizeof(LinkedList));
    for (int i = 0; i < vertices; ++i) {
        graph->array[i].head = NULL;
    }
    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
}

int* shortestPath(Graph* graph, int source) {
    bool* visited = (bool*)malloc(graph->vertices * sizeof(bool));
    int* distance = (int*)malloc(graph->vertices * sizeof(int));
    for (int i = 0; i < graph->vertices; ++i) {
        visited[i] = false;
        distance[i] = -1;
    }

    visited[source] = true;
    distance[source] = 0;

    int queue[MAX_VERTICES];
    int front = 0, rear = 0;
    queue[rear++] = source;

    while (front < rear) {
        int currentVertex = queue[front++];
        Node* temp = graph->array[currentVertex].head;
        while (temp != NULL) {
            int adjVertex = temp->vertex;
            if (!visited[adjVertex]) {
                visited[adjVertex] = true;
                distance[adjVertex] = distance[currentVertex] + 1;
                queue[rear++] = adjVertex;
            }
            temp = temp->next;
        }
    }

    free(visited);
    return distance;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N, M;
    scanf("%d %d", &N, &M);

    Graph* graph = createGraph(N);

    int u, v;
    for (int i = 0; i < M; ++i) {
        scanf("%d %d", &u, &v);
        addEdge(graph, u - 1, v - 1);
    }

    int* distances = shortestPath(graph, 0);

    for (int i = 0; i < N; ++i) {
        printf("%d\n", distances[i]);
    }

    free(distances);
    return 0;
}
