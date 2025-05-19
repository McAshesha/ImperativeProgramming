#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int n;
    scanf("%d", &n);
    getchar();

    int target[n][n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int c = getchar();
            target[i][j] = (c == '*') ? 1 : 0;
        }
        getchar();
    }

    int eq = n * n;
    int var = eq;

    // Создаем расширенную матрицу для системы уравнений
    char **matrix = (char **) malloc(eq * sizeof(char *));
    for (int i = 0; i < eq; i++)
    {
        matrix[i] = (char *) malloc((var + 1) * sizeof(char));
        memset(matrix[i], 0, (var + 1) * sizeof(char));
    }

    // Заполняем матрицу уравнений
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int row = i * n + j;
            matrix[row][var] = target[i][j]; // Правая часть уравнения

            // Текущая клетка (i, j)
            int idx = i * n + j;
            matrix[row][idx] ^= 1;

            // Соседние клетки
            if (i > 0)
            { // Вверх
                idx = (i - 1) * n + j;
                matrix[row][idx] ^= 1;
            }
            if (i < n - 1)
            { // Вниз
                idx = (i + 1) * n + j;
                matrix[row][idx] ^= 1;
            }
            if (j > 0)
            { // Влево
                idx = i * n + (j - 1);
                matrix[row][idx] ^= 1;
            }
            if (j < n - 1)
            { // Вправо
                idx = i * n + (j + 1);
                matrix[row][idx] ^= 1;
            }
        }
    }

    // Метод Гаусса
    int rank = 0;
    for (int col = 0; col < var; col++)
    {
        // Поиск ведущего элемента
        int pivot = -1;
        for (int i = rank; i < eq; i++)
        {
            if (matrix[i][col])
            {
                pivot = i;
                break;
            }
        }
        if (pivot == -1)
        {
            continue;
        }

        // Обмен строк
        char *tmp = matrix[rank];
        matrix[rank] = matrix[pivot];
        matrix[pivot] = tmp;

        // Обнуление столбца
        for (int i = 0; i < eq; i++)
        {
            if (i != rank && matrix[i][col])
            {
                for (int j = col; j <= var; j++)
                {
                    matrix[i][j] ^= matrix[rank][j];
                }
            }
        }
        rank++;
    }

    // Находим решение
    char *solution = (char *)calloc(var, sizeof(char));
    for (int i = 0; i < rank; i++)
    {
        int lead_col = -1;
        for (int j = 0; j < var; j++)
        {
            if (matrix[i][j])
            {
                lead_col = j;
                break;
            }
        }
        if (lead_col == -1)
        {
            continue;
        }
        solution[lead_col] = matrix[i][var];
    }

    // Собираем и выводим результат
    int count = 0;
    for (int i = 0; i < var; i++)
    {
        if (solution[i])
        {
            count++;
        }
    }
    printf("%d\n", count);

    for (int i = 0; i < var; i++)
    {
        if (solution[i])
        {
            int x = i / n + 1;
            int y = i % n + 1;
            printf("%d %d\n", x, y);
        }
    }

    for (int i = 0; i < eq; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
    free(solution);

    return 0;
}