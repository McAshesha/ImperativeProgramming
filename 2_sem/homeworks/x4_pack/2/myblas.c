#include "cblas.h"

void myblas_dgemm(int layout, int transA, int transB, int M, int N, int K, double alpha, const double *A, int lda, const double *B, int ldb, double beta, double *C, int ldc) {
    int i, j, k;
    if (transA == 111 && transB == 111) {
        for (i = 0; i < M; ++i) {
            for (j = 0; j < N; ++j) {
                double sum = 0.0;
                for (k = 0; k < K; ++k) {
                    sum += A[i * lda + k] * B[k * ldb + j];
                }
                C[i * ldc + j] = alpha * sum + beta * C[i * ldc + j];
            }
        }
    }
}
