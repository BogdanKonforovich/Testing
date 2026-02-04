#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <windows.h>
#define min_x 1E-15
#define max_x 1E15
#define min_k -32768
#define max_k 32767
#define min_E 1
#define max_E 15
#define ne0 0
#define max_iter 1000

int size (double a, char name){
    if ((fabs(a) < min_x || fabs(a) > max_x) && a != 0) {
        printf ("%c задано в неправильному діапазоні\nПовторіть спробу введення %c\n", name, name );
        return 1;
    }
    return 0;
}

int main() {

    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    
    int E, k, i = 1, j;
    double x, y, yi = 1, yk = 1, delta = 1, toch;
    char m, en, xn = 'x', kn = 'k', En = 'E', yn = 'y';
    
    do {
        printf("Введіть значення %c (|%c| повинно від %g до %g):",xn, xn, min_x , max_x);
        do {
            m=0;
            if(scanf ("%lf%c", &x, &en) != 2 || en!='\n')
            {
                printf ("Введіть %c в правильній формі!(Приклад: 1.43)\nПовторіть спробу введення %c\n", xn, xn);
                m=1;
                while (getchar() != '\n'); // чистимо буфер
            } 
            else {
                if (size (x, xn) == 1) {
                    m = 1;
                }
            }
        } 
        while (m);

        printf("Введіть значення %c (%c повинно бути від %d до %d та не дорівнювати %d):",kn, kn , min_k , max_k, ne0);
        do {
            m=0;
            if(scanf ("%d%c", &k, &en) != 2 || en!='\n')
            {
                printf ("Введіть %c в правильній формі!(Тільки цілі числа)\nПовторіть спробу введення %c\n", kn, kn);
                m=1;
                while (getchar() != '\n'); // чистимо буфер
            } 
            else {
                if (k < min_k || k > max_k) {
                    m = 1;
                    printf ("%c задано в неправильному діапазоні\nПовторіть спробу введення %c\n", kn, kn);
                } else{
                    if(k==ne0){
                        m = 1;
                        printf ("%c повинно не дорівнювати %d\nПовторіть спробу введення %c\n", kn, ne0, kn);
                    }   
                } 
            }
        } 
        while (m);

        if (k > ne0){
            if (k%2 == ne0 && x < ne0){
                printf ("На жаль знайти корінь з такими значеннями %c та %c неможливо!\n", xn, kn);
                m = 1;
            }
        }
        else {
            if (k%2 == ne0 && x <= 0){
                printf ("На жаль знайти корінь з такими значеннями %c та %c неможливо!\n", xn, kn);
                m = 1;
            }
            if (k%2 != ne0 && x == 0){
                printf ("На жаль знайти корінь з такими значеннями %c та %c неможливо!\n", xn, kn);
                m = 1;
            }
        }

        if (m == 0){
            printf("Введіть значення %c (точність обчислень) (%c повинно від %d до %d):",En, En, min_E , max_E);
            do {
                m=0;
                if(scanf ("%d%c", &E, &en) != 2 || en!='\n')
                {
                    printf ("Введіть %c в правильній формі!(Тільки цілі числа)\nПовторіть спробу введення %c\n", En, En);
                    m=1;
                    while (getchar() != '\n'); // чистимо буфер
                } 
                else {
                    if (E < min_E || E > max_E) {
                        printf ("%c задано в неправильному діапазоні\nПовторіть спробу введення %c\n", En, En);
                        m = 1;
                    }
                }
            } 
            while (m);
        
            if (k != 1){
                toch = pow(10.0, -E);

                i = 1;
                if (k > 0){
                    do {
                        yk=pow(yi,k-1);
                        delta = (1.0/k)*((x/yk)-yi);
                        if (fabs(delta) < toch){
                            yi = yi + delta;
                            printf("y = %.*lf\n",E , yi);
                            m = 0;
                        } else {
                            // printf("Кількість ітерацій: %d, Delta = %.*lf, y = %.*lf\n", i, E, delta, E, yi);
                            yi = yi + delta;
                            i++;
                            if (i > max_iter) {
                                printf("Досягнуто максимальну кількість ітерацій (%d). Розрахунок припинено.\n", max_iter);
                                printf("Останнє значення y = %.*lf\n",E , yi);
                                m = 0;}
                                else  
                                m = 1;
                        }
                    } while (m);
                }
                if (k < 0){
                    do {
                        yk=pow(yi,fabs(k)-1);
                        delta = (1.0/fabs(k))*((x/yk)-yi);
                        if (fabs(delta) < toch){
                            yi = yi + delta;
                            if (yi == 0){
                                printf ("На жаль знайти корінь з такими значеннями %c та %c неможливо!\n", xn, kn);
                            }
                            else{
                            printf("y = %.*lf\n", E, 1.0 / yi);
                            m = 0;
                            }
                        } else {
                            if (yi == 0){
                                printf ("На жаль знайти корінь з такими значеннями %c та %c неможливо!\n", xn, kn);
                            }
                            else{
                            // printf("Кількість ітерацій: %d, Delta = %.*lf, y = %.*lf\n", i, E, delta, E, 1/yi);
                            yi = yi + delta;
                            i++;
                            if (i > max_iter) {
                                printf("Досягнуто максимальну кількість ітерацій (%d). Розрахунок припинено.\n", max_iter);
                                printf("Останнє значення y = %.*lf\n",E , 1/yi);
                                m = 0;}
                                else  
                                m = 1;
                            }
                        }
                    } while (m);
                }
            } 
            if (k == 1){
            y = x;
            printf("y = %.*lf\n", E, y);
            }
        }
        
        printf ("Щоб закінчити програму, натисніть ESC!\n" "Якщо хочете продовжити, натисніть Enter\n");
    }
    while (getch()!=27);
    return 0; 
}