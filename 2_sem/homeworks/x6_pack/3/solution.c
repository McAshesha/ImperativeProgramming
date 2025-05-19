#include <stdio.h>
#include <limits.h>

#define MAX_N 101
#define INF INT_MAX

int N, K;
int capacity[MAX_N][MAX_N]; // Пропускные способности
int flow[MAX_N][MAX_N];     // Потоки
int parent[MAX_N];          // Для хранения предков в пути

int findPath(int source, int sink) {
    int visited[MAX_N] = {0};
    int queue[MAX_N];
    int front = 0, rear = 0;
    queue[rear++] = source;
    visited[source] = 1;
    parent[source] = -1;

    while (front < rear) {
        int u = queue[front++];
        for (int v = 0; v < N; v++) {
            if (!visited[v] && capacity[u][v] - flow[u][v] > 0) {
                queue[rear++] = v;
                parent[v] = u;
                visited[v] = 1;
            }
        }
    }
    return visited[sink];
}

// Поиск максимального потока методом Форда-Фалкерсона
int fordFulkerson(int source, int sink) {
    int maxFlow = 0;
    while (findPath(source, sink)) {
        int pathFlow = INF;
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            pathFlow = pathFlow < (capacity[u][v] - flow[u][v]) ? pathFlow : (capacity[u][v] - flow[u][v]);
        }
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            flow[u][v] += pathFlow;
            flow[v][u] -= pathFlow;
        }
        maxFlow += pathFlow;
    }
    return maxFlow;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    scanf("%d %d", &N, &K);
    for (int i = 0; i < K; i++) {
        int u, v, c;
        scanf("%d %d %d", &u, &v, &c);
        capacity[u - 1][v - 1] = c; // Приводим к нумерации с 0
        capacity[v - 1][u - 1] = c; // Обратное ребро
    }

    int maxFlow = fordFulkerson(0, N - 1);
    printf("%d\n", maxFlow);

    return 0;
}
