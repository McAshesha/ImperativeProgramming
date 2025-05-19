#include "sol.h"

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 300000
#define MAX_EDGES 300000

// Structure to represent a node in the adjacency list
typedef struct Node {
    int vertex;
    int weight;
    struct Node* next;
} Node;

// Structure to represent the adjacency list
typedef struct {
    Node* head;
} AdjList;

// Structure to represent the graph
typedef struct {
    int numVertices;
    AdjList* array;
} Graph;

// Function to create a new node
Node* createNode(int v, int weight) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// Function to initialize a graph with given number of vertices
Graph* createGraph(int numVertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = numVertices;

    // Create an array of adjacency lists. Size of the array will be numVertices
    graph->array = (AdjList*)malloc(numVertices * sizeof(AdjList));

    // Initialize each adjacency list as empty by making head as NULL
    for (int i = 0; i < numVertices; ++i)
        graph->array[i].head = NULL;

    return graph;
}

// Function to add an edge to an undirected graph
void addEdge(Graph* graph, int src, int dest, int weight) {
    // Add an edge from src to dest
    Node* newNode = createNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // Since the graph is undirected, add an edge from dest to src also
    newNode = createNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// Function to free memory allocated for the graph
void freeGraph(Graph* graph) {
    if (graph) {
        if (graph->array) {
            for (int v = 0; v < graph->numVertices; ++v) {
                Node* current = graph->array[v].head;
                while (current) {
                    Node* temp = current;
                    current = current->next;
                    free(temp);
                }
            }
            free(graph->array);
        }
        free(graph);
    }
}

// Global variables to hold graph data
static Graph* graph = NULL;
static int* edgesCount = NULL;
static Edge* incidentEdges = NULL;

// Function to initialize the graph
void init() {
    int numVertices = getVerticesCount();
    graph = createGraph(numVertices);
    edgesCount = (int*)calloc(numVertices, sizeof(int));

    Edge edge;
    while (readEdge(&edge)) {
        addEdge(graph, edge.from, edge.to, edge.weight);
        edgesCount[edge.from]++;
        edgesCount[edge.to]++;
    }

    incidentEdges = (Edge*)malloc(MAX_EDGES * sizeof(Edge));
}

// Function to get the number of edges incident to a vertex
int getEdgesCount(int iVertex) {
    return edgesCount[iVertex];
}

// Function to get the iIndex-th edge incident to the vertex iVertex
Edge getIncidentEdge(int iVertex, int iIndex) {
    Node* current = graph->array[iVertex].head;
    int count = 0;
    while (current) {
        if (count == iIndex) {
            incidentEdges[count] = (Edge){iVertex, current->vertex, current->weight};
            return incidentEdges[count];
        }
        count++;
        current = current->next;
    }
    // Should not reach here ideally, returning an edge with all zeros
    return (Edge){0, 0, 0};
}
