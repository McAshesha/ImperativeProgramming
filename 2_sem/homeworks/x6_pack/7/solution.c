#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 10
#define MAXK 10
#define MAXM 100

int N, K, M, L;
int effect[MAXN][MAXK][MAXM];
int cur[MAXM];
int sol[MAXN];

// Флаг, что решение найдено
void dfs(int idx) {
    if (idx == N) {
        // Проверяем, что все лампочки имеют напряжение L
        for (int t = 0; t < M; t++) {
            if (cur[t] != L) return;
        }
        // Вывод решения и завершение
        printf("YES\n");
        for (int i = 0; i < N; i++) {
            printf("%d\n", sol[i] + 1);
        }
        exit(0);
    }

    int rem = N - idx - 1;
    for (int j = 0; j < K; j++) {
        // Пробуем включить j-й переключатель на пульте idx
        int ok = 1;
        for (int t = 0; t < M; t++) {
            cur[t] += effect[idx][j][t];
            if (cur[t] > L) ok = 0;
        }
        if (!ok) {
            // Откатываем и пробуем следующий
            for (int t = 0; t < M; t++) {
                cur[t] -= effect[idx][j][t];
            }
            continue;
        }
        // Отсечение: проверяем, можно ли достичь L даже в лучшем случае
        for (int t = 0; t < M; t++) {
            if (cur[t] + rem < L) {
                ok = 0;
                break;
            }
        }
        if (ok) {
            sol[idx] = j;
            dfs(idx + 1);
        }
        // Откат
        for (int t = 0; t < M; t++) {
            cur[t] -= effect[idx][j][t];
        }
    }
}

int main() {
    if (scanf("%d %d %d %d", &N, &K, &M, &L) != 4) return 0;

    // Считываем N*K строк по M символов, пропуская пустые строки
    char line[MAXM + 5];
    int count = 0;
    while (count < N * K && fgets(line, sizeof(line), stdin)) {
        // Ищем первую строку, содержащую X или .
        if (strchr(line, 'X') == NULL && strchr(line, '.') == NULL) {
            continue;
        }
        // Убедимся, что длина достаточная
        int len = strlen(line);
        while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r')) {
            line[--len] = '\0';
        }
        if (len < M) {
            // Неполная строка ? пропускаем
            continue;
        }
        int i = count / K;
        int j = count % K;
        for (int t = 0; t < M; t++) {
            effect[i][j][t] = (line[t] == 'X') ? 1 : 0;
        }
        count++;
    }

    // Инициализация текущих напряжений
    for (int t = 0; t < M; t++) cur[t] = 0;

    dfs(0);

    // Если решения нет
    printf("NO\n");
    return 0;
}
