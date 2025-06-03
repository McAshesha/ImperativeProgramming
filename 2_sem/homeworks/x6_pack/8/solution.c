#include <stdio.h>
#include <stdbool.h>

#define MAX_N 10
#define MAX_K 10
#define MAX_M 100

static int  N;                          // number of switch-rows
static int  K;                          // switches per row
static int  M;                          // lamps per row
static int  L;                          // target ?on? count per lamp

// effect[row][switch][lamp] is 0 or 1
static int effect[MAX_N][MAX_K][MAX_M];
// current sum of "on" counts per lamp
static int currentSum[MAX_M];
// best remaining possible per lamp from row i onward
static int     maxRemaining[MAX_N+1][MAX_M];
// solution[row] = chosen switch index (0-based)
static int solution[MAX_N];

static bool dfsSearch(int row)
{
    if (row == N)
    {
        for (int t = 0; t < M; t++)
        {
            if (currentSum[t] != L)
            {
                return false;
            }
        }
        return true;
    }

    for (int sw = 0; sw < K; sw++)
    {
        bool ok = true;

        // apply switch effect
        for (int t = 0; t < M; t++)
        {
            currentSum[t] += effect[row][sw][t];
            if (currentSum[t] > L)
            {
                ok = false;
            }
        }

        // prune: can we still reach L on each lamp?
        if (ok)
        {
            for (int t = 0; t < M; t++)
            {
                if (currentSum[t] + maxRemaining[row+1][t] < L)
                {
                    ok = false;
                    break;
                }
            }
        }

        if (ok)
        {
            solution[row] = sw;
            if (dfsSearch(row + 1))
            {
                return true;
            }
        }

        // undo changes
        for (int t = 0; t < M; t++)
        {
            currentSum[t] -= effect[row][sw][t];
        }
    }

    return false;
}

int main(void)
{
    scanf("%d %d %d %d", &N, &K, &M, &L);

    // portable parsing: read exactly N*K*M of 'X' or '.'
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < K; j++)
        {
            for (int t = 0; t < M; t++)
            {
                int c = getchar();
                while (c != 'X' && c != '.')
                {
                    c = getchar();
                }
                effect[i][j][t] = (c == 'X');
            }
        }
    }

    // zero out current sums
    for (int t = 0; t < M; t++)
    {
        currentSum[t] = 0;
    }

    // build maxRemaining[row][t]
    for (int t = 0; t < M; t++)
    {
        maxRemaining[N][t] = 0;
    }
    for (int i = N - 1; i >= 0; i--)
    {
        for (int t = 0; t < M; t++)
        {
            int best = 0;
            for (int j = 0; j < K; j++)
            {
                if (effect[i][j][t] > best)
                {
                    best = effect[i][j][t];
                }
            }
            maxRemaining[i][t] = maxRemaining[i+1][t] + best;
        }
    }

    if (dfsSearch(0))
    {
        printf("YES\n");
        for (int i = 0; i < N; i++)
        {
            printf("%d\n", solution[i] + 1);
        }
    }
    else
    {
        printf("NO");
    }

    return 0;
}
