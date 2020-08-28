#include <stdio.h>
#include <stdlib.h>

int CheckV(const int* matrix, int n, int m)
{
    int flag1;
    int flag2;
    int result = 0;

    for (int i = 0; i < m; i++)
    {
        flag1 = 0;
        flag2 = 0;


        for (int j = 1; j < n; j++)
        {
            printf("%d %d\n\n", matrix[j * m + i], matrix[(j - 1) * m + i]);
            if (matrix[j * m + i] > matrix[(j - 1) * m + i])
                flag1++;
            printf("%d %d\n\n", matrix[j * m + i], matrix[(j - 1) * m + i]);
            if (matrix[j * m + i] < matrix[(j - 1) * m + i])
                flag2++;
        }

        if (flag1 == 0 || flag2 == 0)
            result++;
    }

    return result;
}

int CheckG(const int* matrix, int n, int m)
{
    int flag1;
    int flag2;
    int result = 0;

    for (int i = 0; i < n; i++) {
        flag1 = 0;
        flag2 = 0;

        for (int j = 1; j < m; j++)
        {
            printf("%d %d\n\n", matrix[m * i + j - 1], matrix[m * i + j]);
            if (matrix[m * i + j - 1] > matrix[m * i + j])
                flag1++;
            printf("%d %d\n\n", matrix[m * i + j - 1], matrix[m * i + j]);
            if (matrix[m * i + j - 1] < matrix[m * i + j])
                flag2++;
        }

        if (flag1 == 0 || flag2 == 0)
            result++;
    }

    return result;
}

int main() {

    int n = 0;
    int m = 0;
    int count = 0;
    int flag1 = 0;
    int flag2 = 0;

    int* matrix;

    printf("Введите размер матрицы(Два целых числа, M x N): ");

    scanf("%d%d", &n, &m);

    matrix = (int*)malloc(n * m * sizeof (int));

    printf("Введите матрицу: ");

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &matrix[i * m + j]);
        }

    count = CheckV(matrix, n, m) + CheckG(matrix, n, m);

    printf("%d", count);

    free(matrix);

    return 0;
}
