#include <stdio.h>
#include <math.h>
#include <windows.h>

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    int n = 1, i = 0;
    double x, S = 1, Sn, S0 = 1, E, M;
    
    printf("Введіть значення x (|x| < 1): ");
    scanf("%lf", &x);
    printf("Введіть точність обчислень E (0 < E < 1): ");
    scanf("%lf", &E);

    Sn = (0.5 - (n - 1)) * x / n * S0;
    S += Sn;  

    while (fabs(Sn) >= E) {
        n++;
        S0 = Sn;
        Sn = (0.5 - (n - 1)) * x / n * S0;
        S += Sn;
    }

    M = E;
    while (M < 1) {
        M *= 10;
        i++;
    }
    printf("Значення суми ряду S = %.*lf\n", i, S);
    printf("Контрольне значення sqrt(1 + x) = %.*lf\n", i, sqrt(1 + x));

    system("pause");
    return 0;
}
