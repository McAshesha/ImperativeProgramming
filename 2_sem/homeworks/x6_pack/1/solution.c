#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 12

int M, N;
char field[MAX_SIZE][MAX_SIZE];
int col[MAX_SIZE], hasV[MAX_SIZE], hasS[MAX_SIZE * 2], hasD[MAX_SIZE * 2];

void rec(int r) {
    if (r == M) {
        printf("YES\n");
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (col[i] == j)
                    printf("X");
                else
                    printf(".");
            }
            printf("\n");
        }
        exit(0);
    }

    for (int c = 0; c < N; c++) {
        if (field[r][c] == '.' || hasV[c] || hasS[r+c] || hasD[r-c+N])
            continue;

        col[r] = c;
        hasV[c] = hasS[r+c] = hasD[r-c+N] = 1;
        rec(r + 1);
        hasV[c] = hasS[r+c] = hasD[r-c+N] = 0;
    }
}


int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    scanf("%d %d", &M, &N);

    for (int i = 0; i < M; i++) {
        scanf("%s", field[i]);
    }

    rec(0);
    printf("NO\n");

    return 0;
}
