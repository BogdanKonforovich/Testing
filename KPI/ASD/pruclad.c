#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <float.h>

// Функція обміну двох рядків
void swapRows(double M[][50], int r1, int r2, int m) {
    for (int j = 0; j < m; j++) {
        double tmp = M[r1][j];
        M[r1][j] = M[r2][j];
        M[r2][j] = tmp;
    }
}

// Функція, що створює нову матрицю з переставленими рядками
void buildMatrix(double src[][50], double dst[][50], int n, int m) {
    double min_val = DBL_MAX, max_val = -DBL_MAX;
    int r_min = 0, r_max = 0;

    // Копіюємо матрицю в dst
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            dst[i][j] = src[i][j];

    // Шукаємо рядки з мінімальним та максимальним елементами
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (src[i][j] < min_val) {
                min_val = src[i][j];
                r_min = i;
            }
            if (src[i][j] > max_val) {
                max_val = src[i][j];
                r_max = i;
            }
        }
    }

    // Міняємо рядки місцями
    if (r_min != r_max) {
        swapRows(dst, r_min, r_max, m);
    }
}

// Вивід матриці
void printMatrix(double M[][50], int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%7.2f ", M[i][j]);
        }
        printf("\n");
    }
}

int main() {
        SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    int n, m;

    printf("Введіть n та m: ");
    scanf("%d %d", &n, &m);

    double C[50][50], B[50][50];
    double Y[50][50], Z[50][50];

    printf("Введіть матрицю C:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%lf", &C[i][j]);

    printf("Введіть матрицю B:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%lf", &B[i][j]);

    buildMatrix(C, Y, n, m);
    buildMatrix(B, Z, n, m);

    printf("\nМатриця Y (з C після перестановки):\n");
    printMatrix(Y, n, m);

    printf("\nМатриця Z (з B після перестановки):\n");
    printMatrix(Z, n, m);
    system("pause");
    return 0;
}
