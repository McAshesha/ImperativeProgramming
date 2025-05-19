#include <stdio.h>
#include <stdint.h>

int N;

void Init(const int *arr, int n);

int64_t Sum(int l, int r);

int Query(int l, int64_t sum);

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int M;
    scanf("%d %d", &N, &M);

    int arr[N];
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &arr[i]);
    }

    Init(arr, N);

    for (int i = 0; i < M; i++)
    {
        int L;
        int64_t S;
        scanf("%d %lld", &L, &S);

        int R = Query(L, S);
        printf("%d\n", R);
    }

    return 0;
}
