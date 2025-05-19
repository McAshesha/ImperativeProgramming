#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define K 4000          // Увеличенное количество отрезков
#define POLY_DEGREE 6   // Увеличенная степень полинома

typedef struct {
    double w, a, b;
} Term;

double **coeffs;  // Коэффициенты полиномов для каждого отрезка
Term *terms;       // Параметры слагаемых функции
int N;             // Количество слагаемых

// Решение СЛАУ методом Гаусса для матрицы (POLY_DEGREE+1)x(POLY_DEGREE+2)
int gauss(double A[7][8], double x[7]) {
    int n = POLY_DEGREE + 1;
    for (int i = 0; i < n; i++) {
        // Поиск ведущего элемента
        int max_row = i;
        for (int k = i + 1; k < n; k++) {
            if (fabs(A[k][i]) > fabs(A[max_row][i])) {
                max_row = k;
            }
        }
        // Обмен строк
        if (max_row != i) {
            for (int k = i; k <= n; k++) {
                double tmp = A[i][k];
                A[i][k] = A[max_row][k];
                A[max_row][k] = tmp;
            }
        }
        // Проверка на вырожденность
        if (fabs(A[i][i]) < 1e-15) {
            return 0;
        }
        // Нормализация строки
        double pivot = A[i][i];
        for (int k = i; k <= n; k++) {
            A[i][k] /= pivot;
        }
        // Исключение элементов ниже
        for (int k = i + 1; k < n; k++) {
            double factor = A[k][i];
            for (int j = i; j <= n; j++) {
                A[k][j] -= factor * A[i][j];
            }
        }
    }
    // Обратный ход
    for (int i = n - 1; i >= 0; i--) {
        x[i] = A[i][n];
        for (int j = i + 1; j < n; j++) {
            x[i] -= A[i][j] * x[j];
        }
    }
    return 1;
}

// Вычисление коэффициентов полиномов для всех отрезков
void compute_coefficients() {
    double h = 1.0 / K;
    coeffs = (double **)malloc(K * sizeof(double *));
    for (int k = 0; k < K; k++) {
        coeffs[k] = (double *)malloc((POLY_DEGREE + 1) * sizeof(double));
        double start = k * h;
        double y[7];
        // Вычисление значений функции в узлах интерполяции
        for (int j = 0; j <= POLY_DEGREE; j++) {
            double s = (double)j / POLY_DEGREE;
            double x = start + s * h;
            y[j] = 0.0;
            for (int i = 0; i < N; i++) {
                y[j] += terms[i].w * cos(terms[i].a * x + terms[i].b);
            }
        }
        // Построение матрицы системы
        double A[7][8];
        for (int j = 0; j <= POLY_DEGREE; j++) {
            double s = (double)j / POLY_DEGREE;
            double pow_s = 1.0;
            for (int m = 0; m <= POLY_DEGREE; m++) {
                A[j][m] = pow_s;
                pow_s *= s;
            }
            A[j][POLY_DEGREE + 1] = y[j];
        }
        // Решение системы и сохранение коэффициентов
        if (!gauss(A, coeffs[k])) {
            fprintf(stderr, "Matrix is singular.\n");
            exit(1);
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int M;
    scanf("%d %d", &N, &M);
    terms = (Term *)malloc(N * sizeof(Term));
    for (int i = 0; i < N; i++) {
        scanf("%lf %lf %lf", &terms[i].w, &terms[i].a, &terms[i].b);
    }
    compute_coefficients();

    double h = 1.0 / K;
    for (int i = 0; i < M; i++) {
        double x;
        scanf("%lf", &x);
        if (x >= 1.0) x = 1.0 - 1e-12; // Корректировка для x=1.0

        int k = (int)(x * K);
        if (k >= K) k = K - 1;
        double start = k * h;
        double s = (x - start) / h;

        double res = 0.0, s_pow = 1.0;
        for (int m = 0; m <= POLY_DEGREE; m++) {
            res += coeffs[k][m] * s_pow;
            s_pow *= s;
        }
        printf("%.15f\n", res);
    }

    // Освобождение памяти
    for (int k = 0; k < K; k++) free(coeffs[k]);
    free(coeffs);
    free(terms);
    return 0;
}