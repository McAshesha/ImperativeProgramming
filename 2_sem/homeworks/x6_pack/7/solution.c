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

// ����, �� �襭�� �������
void dfs(int idx) {
    if (idx == N) {
        // �஢��塞, �� �� �����窨 ����� ����殮��� L
        for (int t = 0; t < M; t++) {
            if (cur[t] != L) return;
        }
        // �뢮� �襭�� � �����襭��
        printf("YES\n");
        for (int i = 0; i < N; i++) {
            printf("%d\n", sol[i] + 1);
        }
        exit(0);
    }

    int rem = N - idx - 1;
    for (int j = 0; j < K; j++) {
        // �஡㥬 ������� j-� ��४���⥫� �� ���� idx
        int ok = 1;
        for (int t = 0; t < M; t++) {
            cur[t] += effect[idx][j][t];
            if (cur[t] > L) ok = 0;
        }
        if (!ok) {
            // �⪠�뢠�� � �஡㥬 ᫥���騩
            for (int t = 0; t < M; t++) {
                cur[t] -= effect[idx][j][t];
            }
            continue;
        }
        // ���祭��: �஢��塞, ����� �� ������ L ���� � ���襬 ��砥
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
        // �⪠�
        for (int t = 0; t < M; t++) {
            cur[t] -= effect[idx][j][t];
        }
    }
}

int main() {
    if (scanf("%d %d %d %d", &N, &K, &M, &L) != 4) return 0;

    // ���뢠�� N*K ��ப �� M ᨬ�����, �ய�᪠� ����� ��ப�
    char line[MAXM + 5];
    int count = 0;
    while (count < N * K && fgets(line, sizeof(line), stdin)) {
        // �饬 ����� ��ப�, ᮤ�ঠ��� X ��� .
        if (strchr(line, 'X') == NULL && strchr(line, '.') == NULL) {
            continue;
        }
        // ��������, �� ����� �����筠�
        int len = strlen(line);
        while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r')) {
            line[--len] = '\0';
        }
        if (len < M) {
            // �������� ��ப� ? �ய�᪠��
            continue;
        }
        int i = count / K;
        int j = count % K;
        for (int t = 0; t < M; t++) {
            effect[i][j][t] = (line[t] == 'X') ? 1 : 0;
        }
        count++;
    }

    // ���樠������ ⥪��� ����殮���
    for (int t = 0; t < M; t++) cur[t] = 0;

    dfs(0);

    // �᫨ �襭�� ���
    printf("NO\n");
    return 0;
}
