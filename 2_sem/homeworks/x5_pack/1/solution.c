#include <stdio.h>
#include <stdlib.h>

#pragma comment(linker, "/STACK:50000000") // Увеличиваем размер стека до 50 мегабайт

#define MAX_SIZE 1010

int N;
char labyrinth[MAX_SIZE][MAX_SIZE];
int visited[MAX_SIZE][MAX_SIZE];

int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, 1, 0, -1 };

void dfs(int x, int y)
{
    if (x < 0 || x >= N || y < 0 || y >= N || labyrinth[x][y] == '*' || visited[x][y])
    {
        return;
    }

    visited[x][y] = 1;

    for (int i = 0; i < 4; i++)
    {
        dfs(x + dx[i], y + dy[i]);
    }
}

int count_unreachable_areas()
{
    int count = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (labyrinth[i][j] == ' ' && !visited[i][j])
            {
                count++;
                dfs(i, j);
            }
        }
    }
    return count;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    char str[MAX_SIZE];
    N = atoi(fgets(str, MAX_SIZE, stdin));

    for (int i = 0; i < N; i++)
    {
        fgets(labyrinth[i], MAX_SIZE, stdin);
    }
    int result = count_unreachable_areas();
    printf("%d\n", result - 1);

    return 0;
}
