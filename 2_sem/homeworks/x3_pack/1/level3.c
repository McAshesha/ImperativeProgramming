#include "myblas.h"

void dgemm(int m, int n, int k, double alpha, const double *A, const double *B, double beta, double *C) {
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            double temp = 0;
            for (int l = 0; l < k; l++)
            {
                temp += A[k*i + l] * B[l*n + j];
            }
            C[i * n + j] *= beta;
            C[i * n + j] += alpha * temp;
        }
    }
}
