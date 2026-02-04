#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <windows.h>

#define RED     "\033[31m"
#define GREEN   "\033[1m\033[32m"
#define RESET   "\033[0m"
#define min_y 1e-6
#define max_y 1e3
#define min_p 1e-3
#define max_p 10
#define min_t 1
#define max_t 12
#define E 1e-7
#define maxiter 5000

double riv1(double n, double m) { return (cos(m / n) - 2 * sin(1 / n) + 1 / n); }
double riv2(double n, double m) { return (sin(log(n)) - cos(log(n)) + m * log(n)); }
double (*riv)(double, double);

void met_1(double (*riv0)(double, double), double y1, double a1, double b1, double eps)
{
    double x = 0, zam = b1;
    char m = 0;
    int iter = 0;

    if ((*riv0)(a1, y1) == 0) {
        printf("x = %.12f\n", a1);
        m = 1;
    } else if ((*riv0)(b1, y1) == 0) {
        printf("x = %.12f\n", b1);
        m = 1;
    }

    if (m != 1) {
        do {
            x = (a1 + b1) / 2.0;
            if (isnan(x) || isinf(x)) {
                m = 1;
            } else {
                if (((*riv0)(a1, y1)) * ((*riv0)(x, y1)) > 0) {
                    a1 = x;
                } else {
                    b1 = x;
                }
            }
            iter++;
            if (iter > maxiter) {
                m = 1;
            }
        } while (fabs(b1 - a1) > eps && m == 0);

        if (m == 0) {
            printf("x = %.12f\n", x);
        } else {
            printf("На жаль програма не змогла обчислити корені\n");
        }
    }
}

void met_2(double (*riv0)(double, double), double y2, double a2, double b2, double eps) {
    double delta = 0.0, pox = 0.0, x = b2;
    char m1 = 0;
    int iter = 0;

    do {
        pox = ((*riv0)(x + E, y2) - (*riv0)(x, y2)) / E;
        if (fabs(pox) < E) {
            printf("На жаль програма не змогла обчислити корені\n");
            m1 = 1;
        } else {
            delta = (*riv0)(x, y2) / pox;
            x = x - delta;
            iter++;
            if (iter > maxiter) {
                printf("На жаль програма не змогла обчислити корені\n");
                m1 = 1;
            }
        }
    } while (fabs(delta) > eps && m1 == 0);

    if (m1 != 1) {
        if (x < a2 || x > b2) {
            printf("На жаль програма не змогла обчислити корені\n");
        } else if (isnan(x) || isinf(x)) {
            printf("На жаль програма не змогла обчислити корені\n");
        } else {
            printf("x = %.12f\n", x);
        }
    }
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    double x, a, b, y;
    int num, toch;
    char m, en;

    do {
        printf("Введіть номер рівняння: 1 - cos(y / x) - 2 * sin(1 / x) + 1 / x, 2 - sin(log(x)) - cos(log(x)) + y * log(x)\n");
        do {
            m = 0;
            if (scanf("%d%c", &num, &en) != 2 || en != '\n') {
                printf(RED "Введіть число в правильній формі! (Тільки число)\n" RESET "Повторіть спробу введення: ");
                m = 1;
                while (getchar() != '\n');
            } else if (num != 1 && num != 2) {
                printf(RED "Ви ввели інше число!\n" RESET "Повторіть спробу введення: ");
                m = 1;
            }
        } while (m);

        if (num == 1) 
        riv = riv1; 
        else 
        riv = riv2;

        printf("Введіть проміжок знаходження коренів (a, b) (їх модуль від %g до %d)\n", min_p, max_p);
        do {
            printf("a: ");
            do {
                m = 0;
                if (scanf("%lf%c", &a, &en) != 2 || en != '\n') {
                    printf(RED "Введіть число в правильній формі! (Тільки число)\n" RESET "Повторіть спробу введення a: ");
                    m = 1;
                    while (getchar() != '\n');
                } else if (fabs(a) < min_p || fabs(a) > max_p) {
                    printf(RED "Введене число не входить в заданий діапазон\n" RESET "Повторіть спробу введення a: ");
                    m = 1;
                } else if (num == 2 && a <= 0) {
                    printf(RED "Для другого рівняння a повиннно бути більшим нуля!\n" RESET "Повторіть спробу введення a: ");
                    m = 1;
                }
            } while (m);

            printf("b: ");
            do {
                m = 0;
                if (scanf("%lf%c", &b, &en) != 2 || en != '\n') {
                    printf(RED "Введіть число в правильній формі! (Тільки число)\n" RESET "Повторіть спробу введення b: ");
                    m = 1;
                    while (getchar() != '\n');
                } else if (fabs(b) < min_p || fabs(b) > max_p) {
                    printf(RED "Введене число не входить в заданий діапазон\n" RESET "Повторіть спробу введення b: ");
                    m = 1;
                }
            } while (m);

            if (a >= b) {
                printf(RED "b повинно бути строго більшим за a!\n" RESET "Повторіть спробу введення \n");
                m = 1;
            } 
            else if ((a + b) == 0) {
                printf(RED "Сума a і b повинно бути більше 0!\n" RESET "Повторіть спробу введення \n");
                m = 1;
            }
        } while (m);

        printf("Введіть значення y  (|y| повиннен бути в межах від %g до %g (0 також підходить))\n", min_y, max_y);
        do {
            m = 0;
            if (scanf("%lf%c", &y, &en) != 2 || en != '\n') {
                printf(RED "Введіть число в правильній формі! (Тільки число)\n" RESET "Повторіть спробу введення y: ");
                m = 1;
                while (getchar() != '\n');
            } else if ((fabs(y) < min_y && y != 0) || fabs(y) > max_y) {
                printf(RED "Введене число не входить в заданий діапазон\n" RESET "Повторіть спробу введення y: ");
                m = 1;
            }
        } while (m);

        printf("Введіть точнісь знаходженя коренів (від %d до %d знаків після коми включно)\n", min_t, max_t);
        do {
            m = 0;
            if (scanf("%d%c", &toch, &en) != 2 || en != '\n') {
                printf(RED "Введіть число в правильній формі! (Введіть ціле число, наприклад 3)\n" RESET "Повторіть спробу введення: ");
                m = 1;
                while (getchar() != '\n');
                while (m);
            } else if (toch < min_t || toch > max_t) {
                printf(RED "Точність задано в неправильному діапазоні\n" RESET "Повторіть спробу введення: ");
                m = 1;
            }
        } while (m);
        double eps = pow(10, -toch);

        printf("Введіть варіан розв'язку рівняння: 1 - метод половинного ділення, 2 - метод дотичних (Ньютона)\n");
        do {
            m = 0;
            if (scanf("%d%c", &num, &en) != 2 || en != '\n') {
                printf(RED "Введіть число в правильній формі! (Тільки число)\n" RESET "Повторіть спробу введення: ");
                m = 1;
                while (getchar() != '\n');
            } else if (num != 1 && num != 2) {
                printf(RED "Ви ввели інше число!\n" RESET "Повторіть спробу введення: ");
                m = 1;
            }
        } while (m);

if (num == 1) {
    double L, R, step, x1, x2, f1, f2;
    L = a;
    R = a;
    step = 0.001;
    x1 = a;
    x2 = a + step;
    m = 0;

    while (x2 <= b && m == 0) {
        f1 = riv(x1, y);
        f2 = riv(x2, y);
        if (!(isnan(f1) || isnan(f2) || isinf(f1) || isinf(f2))) {
            if (f1 * f2 < 0) {
                L = x1;
                R = x2;
                m = 1;
            }
        }
        x1 = x2;
        x2 += step;
    }

    if (!m) {
        printf("На жаль програма не змогла обчислити корені\n");
    } else {
        met_1(riv, y, L, R, eps);
    }
        } else {
            met_2(riv, y, a, b, eps);
        }

        printf("Щоб закінчити програму, натисніть ESC!\nЯкщо хочете ще раз скористатися, натисніть Enter\n");
    } while (getch() != 27);

    return 0;
}
