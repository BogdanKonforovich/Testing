// #include <stdio.h>
// #include <math.h>
// #include <windows.h>

// #define MAX 1000
// #define MIN -1000
// #define MIN_F 0.001
// #define COMA 4

// float fun1(float x, float y);

// float fun2(float x, float y);

// float kor(float (*f)(float, float), float y, float l, float h, float eps, float number);

// int main()
// {
//     SetConsoleCP(65001);
//     SetConsoleOutputCP(65001);
//     int repeat;
//     do
//     {
//         int next = 0, number, variant, error = 0, go = 0, i = 0, amount_ten;
//         char validate, ch;
//         float a, b, epsilon, x, p, q, y, sum, delta, fp;
//         float x1 = a, L, R, step = 0.001;
//         float x2 = a + step;
//         int good = 0;
//         printf("Обери рівняння:\n");
//         printf("1) cos(y/x) - 2*sin(1/x) + 1/x = 0\n");
//         printf("2) sin(ln(x)) - cos(ln(x)) + y*ln(x) = 0\n");
//         while (next == 0)
//         {
//             if (scanf("%d%c", &number, &validate) != 2 || validate != '\n')
//             {
//                 printf("Введено некоректне число!\n");
//                 while ((ch = getchar()) != '\n' && ch != EOF)
//                 {
//                 }
//             }
//             else
//             {
//                 if (number != 1 && number != 2)
//                 {
//                     printf("Впишіть 1, якщо хочеш обрати перше рівняння або 2, якщо друге\n");
//                 }
//                 else
//                 {
//                     next = 1;
//                 }
//             }
//         }
//         printf("Впишіть значення y:\n");
//         next = 0;
//         while (next == 0)
//         {
//             if (scanf("%f%c", &y, &validate) != 2 || validate != '\n')
//             {
//                 printf("Введено некоректне число!\n");
//                 while ((ch = getchar()) != '\n' && ch != EOF)
//                 {
//                 }
//             }
//             else
//             {
//                 if (y > MAX || y < MIN)
//                 {
//                     printf("Число поввино належати діапазону від %d до %d\n", MIN, MAX);
//                 }
//                 else
//                 {
//                     if (fabs(y) < MIN_F)
//                     {
//                         printf("Число занадто маленьке число за модулем не повинно бути меншим ніж %f\n", MIN_F);
//                     }
//                     else
//                     {
//                         next = 1;
//                     }
//                 }
//             }
//         }
//         printf("Впишіть точність. Для цього введи кількість знаків після коми від 1 до %d\n", COMA);
//         next = 0;
//         while (next == 0)
//         {
//             if (scanf("%d%c", &amount_ten, &validate) != 2 || validate != '\n')
//             {
//                 printf("Введено некоректне число!\n");
//                 while ((ch = getchar()) != '\n' && ch != EOF)
//                 {
//                 }
//             }
//             else
//             {
//                 if (amount_ten < 1 || amount_ten > COMA)
//                 {
//                     printf("Кількість знаків після коми повинно бути в межах від 1 до %d\n", COMA);
//                 }
//                 else
//                 {
//                     epsilon = 1 / pow(10.0, amount_ten);
//                     next = 1;
//                 }
//             }
//         }
//         while (good == 0)
//         {
//             printf("Впишіть проміжок знаходження коренів [a, b], b повинно бути більшим за a\n");
//             printf("Впишіть значення a\n");
//             next = 0;
//             while (next == 0)
//             {
//                 if (scanf("%f%c", &a, &validate) != 2 || validate != '\n')
//                 {
//                     printf("Введено некоректне число!\n");
//                     while ((ch = getchar()) != '\n' && ch != EOF)
//                     {
//                     }
//                 }
//                 else
//                 {
//                     if (a > MAX || a < MIN)
//                     {
//                         printf("Число поввино належати діапазону від %d до %d\n", MIN, MAX);
//                     }
//                     else
//                     {
//                         if (fabs(a) < MIN_F)
//                         {
//                             printf("Число занадто маленьке число за модулем не повинно бути меншим ніж %f\n", MIN_F);
//                         }
//                         else
//                         {
//                             next = 1;
//                         }
//                     }
//                 }
//             }
//             printf("Впишіть значення b\n");
//             next = 0;
//             while (next == 0)
//             {
//                 if (scanf("%f%c", &b, &validate) != 2 || validate != '\n')
//                 {
//                     printf("Введено некоректне число!\n");
//                     while ((ch = getchar()) != '\n' && ch != EOF)
//                     {
//                     }
//                 }
//                 else
//                 {
//                     if (number == 1)
//                     {
//                         if (b > MAX || b < MIN)
//                         {
//                             printf("Число поввино належати діапазону від %d до %d\n", MIN, MAX);
//                         }
//                         else
//                         {
//                             if (fabs(b) < MIN_F)
//                             {
//                                 printf("Число занадто маленьке число за модулем не повинно бути меншим ніж %f\n", MIN_F);
//                             }
//                             else
//                             {
//                                 if (a > b)
//                                 {
//                                     printf("b повинно бути більшим за a\n");
//                                 }
//                                 else
//                                 {
//                                     next = 1;
//                                 }
//                             }
//                         }
//                     }
//                     else
//                     {
//                         if (b > MAX || b < MIN_F)
//                         {
//                             printf("Число поввино бути додатнім і належати діапазону від %f до %d\n", MIN_F, MAX);
//                         }
//                         else
//                         {
//                             if (a > b)
//                             {
//                                 printf("b повинно бути більшим за a\n");
//                             }
//                             else
//                             {
//                                 next = 1;
//                             }
//                         }
//                     }
//                 }
//             }
//             printf("Обери метод обчислення:\n");
//             printf("1) методом половинного ділення\n");
//             printf("2) методом дотичних (Ньютона)\n");
//             next = 0;
//             while (next == 0)
//             {
//                 if (scanf("%d%c", &variant, &validate) != 2 || validate != '\n')
//                 {
//                     printf("Введено некоректне число!\n");
//                     while ((ch = getchar()) != '\n' && ch != EOF)
//                     {
//                     }
//                 }
//                 else
//                 {
//                     if (variant != 1 && variant != 2)
//                     {
//                         printf("Впишіть 1, щоб обчислити методом половинного ділення або 2, щоб обчислити методом дотичних\n");
//                     }
//                     else
//                     {
//                         next = 1;
//                     }
//                 }
//             }
//             if (variant == 1)
//             {
//                 if (number == 1)
//                 {
//                     if ((a + b) == 0 || fabs(b - a) < epsilon)
//                     {
//                         printf("Цим методом розв'язати рівняння неможна! Змініть інтервал або метод!\n");
//                     }
//                     else
//                     {
//                         i++;
//                     }
//                 }
//                 else
//                 {
//                     if (a <= 0)
//                     {
//                         printf("a повинно бути  більшим 0 за областю визначеня, змініть інтервал\n");
//                     }
//                     else
//                     {
//                         if ((a + b) <= 0 || fabs(b - a) < epsilon)
//                         {
//                             printf("Цим методом розв'язати рівняння неможна! Змініть інтервал або метод!\n");
//                         }
//                         else
//                         {
//                             i++;
//                         }
//                     }
//                 }
//             }
//             else
//             {
//                 if (number == 1)
//                 {
//                     if (b == 0)
//                     {
//                         printf("Цим методом розв'язати рівняння неможна! Змініть інтервал або метод!\n");
//                     }
//                     else
//                     {
//                         i++;
//                     }
//                 }
//                 else
//                 {
//                     if (a <= 0)
//                     {
//                         printf("a повинно бути  більшим 0 за областю визначеня, змініть інтервал!\n");
//                     }
//                     else
//                     {
//                         i++;
//                     }
//                 }
//             }
//             if (i == 1)
//             {
//                 if (number == 1)
//                 {
//                     while (x2 <= b)
//                     {
//                         if (fun1(x1, y) * fun1(x2, y) < 0)
//                         {
//                             L = x1;
//                             R = x2;
//                             good = 1;
//                         }
//                         x1 = x2;
//                         x2 += step;
//                     }
//                 }
//                 else
//                 {
//                     while (x2 <= b)
//                     {
//                         if (fun2(x1, y) * fun2(x2, y) < 0)
//                         {
//                             L = x1;
//                             R = x2;
//                             good = 1;
//                         }
//                         x1 = x2;
//                         x2 += step;
//                     }
//                 }
//             }
//             if (good != 1 && i != 0)
//             {
//                 printf("Коренів на цьому інтервалі немає, змініть інтервал!\n");
//             }
//         }

//         if (variant == 1)
//         {
//             if (number == 1)
//                 x = kor(fun1, y, L, R, epsilon, number);
//             else
//                 x = kor(fun2, y, L, R, epsilon, number);
//         }
//         else
//         {
//             x = b;
//             do
//             {
//                 if (number == 1)
//                 {
//                     fp = (fun1(x + epsilon, y) - fun1(x, y)) / epsilon;
//                     if (fp == 0)
//                     {
//                         error = 1;
//                     }
//                     else
//                     {
//                         delta = fun1(x, y) / fp;
//                     }
//                 }
//                 else
//                 {
//                     fp = (fun2(x + epsilon, y) - fun2(x, y)) / epsilon;
//                     if (fp == 0)
//                     {
//                         error = 1;
//                     }
//                     else
//                     {
//                         delta = fun2(x, y) / fp;
//                     }
//                 }
//                 x = x - delta;
//                 if (error == 1)
//                 {
//                     delta = fabs(epsilon) - 1;
//                 }
//             } while (fabs(delta) > epsilon);
//         }
//         if (error != 1)
//         {
//             if (x != 0)
//             {
//                 if (x <= b && x >= a)
//                 {
//                     printf("Результат: %f\n", x);
//                 }
//                 else
//                 {
//                     printf("Корення в цьому проміжку немає!\n");
//                 }
//             }
//             else
//             {
//                 printf("Цим методом розв'язати рівняння неможна!\n");
//             }
//         }
//         else
//         {
//             printf("Цим методом розв'язати рівняння неможна!\n");
//         }
//         while (go == 0)
//         {
//             printf("Ти хочеш продовжити? (1 = так, 0 = ні): ");
//             if (scanf("%d%c", &repeat, &validate) != 2 || validate != '\n')
//             {
//                 printf("Введено некоректне число!\n");
//                 while ((ch = getchar()) != '\n' && ch != EOF)
//                 {
//                 }
//             }
//             else
//             {
//                 if (repeat == 0 || repeat == 1)
//                 {
//                     go++;
//                 }
//                 else
//                 {
//                     printf("Введено не ті числа, які потрібно! Введіть 0, щоб завершити роботу програмки, або 1, щоб продовжити!\n");
//                 }
//             }
//         }
//     } while (repeat == 1);

//     return 0;
// }

// float fun1(float x, float y) { return (cos(y / x) - 2 * sin(1.0 / x) + 1.0 / x); }

// float fun2(float x, float y) { return (sin(log(x)) - cos(log(x)) + y * log(x)); }

// float kor(float (*f)(float, float), float y, float l, float h, float eps, float number)
// {
//     float x;
//     while (fabs(h - l) > eps)
//     {
//         x = (l + h) / 2.0;
//         (f(l, y) * f(x, y) > 0) ? (l = x) : (h = x);
//     }
//     return x;
// }
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
#define E 1e-15
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
            break;
        } else {
            delta = (*riv0)(x, y2) / pox;
            x = x - delta;
            iter++;
            if (iter > maxiter) {
                printf("На жаль програма не змогла обчислити корені\n");
                m1 = 1;
                break;
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

        if (num == 1) riv = riv1; else riv = riv2;

        printf("Введіть проміжок знаходження коренів (a, b) (їх модуль від %g до %d)\n", min_p, max_p);
        do {
            printf("a: ");
            do {
                m = 0;
                if (scanf("%lf%c", &a, &en) != 2 || en != '\n') {
                    printf(RED "Введіть число в правильній формі! (Тільки число)\n" RESET "Повторіть спробу введення: ");
                    m = 1;
                    while (getchar() != '\n');
                } else if (fabs(a) < min_p || fabs(a) > max_p) {
                    printf(RED "Введене число не входить в заданий діапазон\n" RESET "Повторіть спробу введення: ");
                    m = 1;
                } else if (num == 2 && a <= 0) {
                    printf(RED "Для другого рівняння a повиннно бути більшим нуля!\n" RESET "Повторіть спробу введення: ");
                    m = 1;
                }
            } while (m);

            printf("b: ");
            do {
                m = 0;
                if (scanf("%lf%c", &b, &en) != 2 || en != '\n') {
                    printf(RED "Введіть число в правильній формі! (Тільки число)\n" RESET "Повторіть спробу введення: ");
                    m = 1;
                    while (getchar() != '\n');
                } else if (fabs(b) < min_p || fabs(b) > max_p) {
                    printf(RED "Введене число не входить в заданий діапазон\n" RESET "Повторіть спробу введення: ");
                    m = 1;
                }
            } while (m);

            if (a >= b) {
                printf(RED "b повинно бути строго більшим за a!\n" RESET "Повторіть спробу введення \n");
                m = 1;
            } else if ((a + b) == 0) {
                printf(RED "Сума a і b повинно бути більше 0!\n" RESET "Повторіть спробу введення \n");
                m = 1;
            }
        } while (m);

        printf("Введіть значення y  (|y| повиннен бути в межах від %g до %g (0 також підходить))\n", min_y, max_y);
        do {
            m = 0;
            if (scanf("%lf%c", &y, &en) != 2 || en != '\n') {
                printf(RED "Введіть число в правильній формі! (Тільки число)\n" RESET "Повторіть спробу введення: ");
                m = 1;
                while (getchar() != '\n');
            } else if ((fabs(y) < min_y && y != 0) || fabs(y) > max_y) {
                printf(RED "Введене число не входить в заданий діапазон\n" RESET "Повторіть спробу введення: ");
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

        // --- пошук підінтервалу зі зміною знаку тільки у разі методу 1
        if (num == 1) {
            double L = a, R = a;
            double step = 0.001;
            double x1 = a;
            double x2 = a + step;
            int found_interval = 0;

            while (x2 <= b && !found_interval) {
                double f1 = riv(x1, y);
                double f2 = riv(x2, y);
                if (isnan(f1) || isnan(f2) || isinf(f1) || isinf(f2)) {
                    // якщо функція не визначена на якомусь кроці, просто просуваємось далі
                    x1 = x2;
                    x2 += step;
                    continue;
                }
                if (f1 * f2 < 0) {
                    L = x1;
                    R = x2;
                    found_interval = 1;
                } else {
                    x1 = x2;
                    x2 += step;
                }
            }

            if (!found_interval) {
                printf("Коренів на цьому інтервалі немає, змініть інтервал!\n");
            } else {
                met_1(riv, y, L, R, eps);
            }
        } else {
            // Якщо вибрали метод Ньютона — запускаємо на всьому [a,b]
            met_2(riv, y, a, b, eps);
        }

        printf("Щоб закінчити програму, натисніть ESC!\nЯкщо хочете ще раз скористатися, натисніть Enter\n");
    } while (getch() != 27);

    return 0;
}
