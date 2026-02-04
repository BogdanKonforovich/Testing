#include <stdio.h>
#include <math.h>
#include <windows.h>

int main() {

    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    float x1, y1, x2, y2, A, B, P, S;
    printf("Введіть координати двох протилежних вершин прямокутника (x1, y1) та (x2, y2):\n");
    scanf("%f %f %f %f", &x1, &y1, &x2, &y2);
    A = fabs(x2 - x1);
    B = fabs(y2 - y1);
    P = 2 * (A + B);
    S = A * B;
    printf("Довжини сторін А та B прямокутника дорівнюють: %.2f %.2f\n", A, B);
    printf("Периметр трямокутника дорівнює: %.2f\n", P);
    printf("Площа прямокутника дорівнює: %.2f \n", S);
    system("pause"); 
    return 0; 
}
