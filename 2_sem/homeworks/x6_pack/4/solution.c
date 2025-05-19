#include <stdio.h>
#include <stdlib.h>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N;
    scanf("%d", &N);

    int* arr = malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }

    int* dp = malloc(N * sizeof(int));
    int* prev = malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        dp[i] = 1;
        prev[i] = -1;
    }

    int max_len = 1, end_index = 0;
    for (int i = 1; i < N; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i] > arr[j] && dp[i] < dp[j] + 1) {
                dp[i] = dp[j] + 1;
                prev[i] = j;
                if (dp[i] > max_len) {
                    max_len = dp[i];
                    end_index = i;
                }
            }
        }
    }

    printf("%d\n", max_len);
    int index = end_index;
    int* output = malloc(max_len * sizeof(int));
    int* index_output = malloc(max_len * sizeof(int));
    int count = 0;
    while (index != -1) {
        output[count] = arr[index];
        index_output[count] = index;
        count++;
        index = prev[index];
    }

    for (int i = max_len - 1; i >= 0; i--) {
        printf("A[%d] = %d\n", index_output[i] + 1, output[i]);
    }

    free(dp);
    free(prev);
    free(output);
    free(index_output);

    return 0;
}
