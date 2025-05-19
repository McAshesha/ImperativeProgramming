#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 102

typedef struct {
    int x, y, dist;
} Point;

int M, N;
char labyrinth[MAX_SIZE][MAX_SIZE];
bool visited[MAX_SIZE][MAX_SIZE];

int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, 1, 0, -1 };

int bfs(Point start, Point end) {
    visited[start.x][start.y] = true;
    Point queue[MAX_SIZE * MAX_SIZE];
    int front = 0, rear = 0;

    queue[rear++] = start;

    while (front < rear) {
        Point current = queue[front++];
        if (current.x == end.x && current.y == end.y) {
            return current.dist;
        }

        for (int i = 0; i < 4; ++i) {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];

            if (nx >= 0 && nx < M && ny >= 0 && ny < N
                    && labyrinth[nx][ny] != 'X' && !visited[nx][ny]) {
                visited[nx][ny] = true;
                queue[rear++] = (Point ) { nx, ny, current.dist + 1 };
                    }
        }
    }

    return -1;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    scanf("%d %d", &M, &N);
    Point start, end;

    for (int i = 0; i < M; ++i) {
        scanf("%s", labyrinth[i]);
        for (int j = 0; j < N; ++j) {
            if (labyrinth[i][j] == 'S') {
                start.x = i;
                start.y = j;
                start.dist = 0;
            }
            if (labyrinth[i][j] == 'F') {
                end.x = i;
                end.y = j;
            }
        }
    }

    int result = bfs(start, end);

    printf("%d\n", result);

    return 0;
}
