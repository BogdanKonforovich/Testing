#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <windows.h> 

#define min 2
#define max 10
#define min_t 1
#define max_t 6
#define min_a 1e-3
#define max_a 1e3
#define P 1000
int main() {

    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    int n, i, j, toch;
    char en, m;

    float **mas_a = NULL;
    float *mas_b = NULL;
    float *sum = NULL;
    float *x1 = NULL;
    float *xp = NULL;

    do{
        printf("Введіть розмір СЛАР (від %d до %d)\n", min, max);
        do{
            m = 0;
            if(scanf("%d%c", &n, &en) != 2 || en != '\n'){
                printf ("Введіть число в правильній формі! (Тільки цілі числа)\nПовторіть спробу введення: ");
                m = 1;
                while (getchar() != '\n');
            }else if(n < min || n > max){
                printf ("Розмір задано в неправильному діапазоні\nПовторіть спробу: ");
                m = 1;
            }
        }
        while (m);
        printf("Введіть точнісь знаходженя коренів (від %d до %d знаків після коми включно)\n", min_t, max_t);
        do{
            m = 0;
            if(scanf("%d%c", &toch, &en) != 2 || en != '\n'){
                printf ("Введіть число в правильній формі! (Введіть ціле число, наприклад 3)\nПовторіть спробу введення: ");
                m = 1;
                while (getchar() != '\n');
            }else if(toch < min_t || toch > max_t){
                printf ("Точність задано в неправильному діапазоні\nПовторіть спробу: ");
                m = 1;
            }
        }
        while (m);
        mas_a = (float**) calloc (n, sizeof(float*));
        if (mas_a == NULL){
            printf("Помилка виділення пам'яті!\n");
            m = 1;
        }
        if (m != 1){
            for(i = 0; i < n && m != 1; i++){
                mas_a[i] = (float*) calloc (n, sizeof(float));
                if (mas_a[i] == NULL){
                    printf("Помилка виділення пам'яті!\n");
                    m = 1;
                }
            }
        }

        if(m != 1){
            mas_b = (float*) calloc (n, sizeof(float));
            if (mas_b == NULL){
                    printf("Помилка виділення пам'яті!\n");
                    m = 1;
                }
        }

        if(m != 1){
            sum = (float*) calloc (n, sizeof(float));
            if (sum == NULL){
                    printf("Помилка виділення пам'яті!\n");
                    m = 1;
                }
        }

        if(m != 1){
            x1 = (float*) calloc (n, sizeof(float));
            if (x1 == NULL){
                    printf("Помилка виділення пам'яті!\n");
                    m = 1;
                }
        }

        if(m != 1){
            xp = (float*) calloc (n, sizeof(float));
            if (xp == NULL){
                    printf("Помилка виділення пам'яті!\n");
                    m = 1;
                }
        }

        if (m != 1){
            printf("Введіть коефіцієнти при х (|а| повиннен бути в межах від %g до %g (0 також підходить)) \n", min_a, max_a);
            for(i = 0; i < n; i++){
                do{
                    m = 0;
                    sum[i] = 0;
                    for(j = 0; j < n; j++){
                        printf("a[%d][%d]\t", i+1, j+1);
                        do{
                            m = 0;
                            if(scanf("%f%c", &mas_a[i][j], &en) != 2 || en != '\n'){
                                printf ("Введіть число в правильній формі! (Дійсне число, наприклад 0.001)\nПовторіть спробу введення: ");
                                m = 1;
                                while (getchar() != '\n');
                            }else if((fabs( mas_a[i][j]*P) < min_a*P && mas_a[i][j] != 0) || fabs(mas_a[i][j]) > max_a){
                                printf ("Число не входить в заданий діапазон!\nПовторіть спробу: ");
                                m = 1;
                            }
                            else if(j == i && mas_a[i][j] == 0){
                                printf("Елемент головної діагонілі (елемент з однаковими індексами) повинен бути більшим 0\nПовторіть спробу введення: ");
                                m = 1;
                            }
                        }
                        while (m);
                        if (j != i) {
                            sum[i] = sum[i] + fabs(mas_a[i][j]);
                        }
                    }
                    if(sum[i] >= fabs(mas_a[i][i])){
                        printf("Елемент головної діагонілі (елемент з однаковими індексами) повинен бути більшим за суму модулів всіх інших елементів. \nПовторіть спробу введення рядку!\n");
                        m = 1;
                    }
                    printf("\n");
                }while (m);
            }

            printf("Введіть значення b (|b| повиннен бути в межах від %g до %g (0 також підходить)) \n", min_a, max_a);
            for(i = 0; i < n; i++){
                do{
                    printf("b[%d]\t", i+1);
                    m = 0;
                    if(scanf("%f%c", &mas_b[i], &en) != 2 || en != '\n'){
                        printf ("Введіть число в правильній формі! (Дійсне число, наприклад 0.001)\nПовторіть спробу введення: ");
                        m = 1;
                        while (getchar() != '\n');
                    }else if((fabs(mas_b[i]) < min_a && mas_b[i] != 0) || fabs(mas_b[i]) > max_a){
                        printf ("Число не входить в заданий діапазон!\nПовторіть спробу: ");
                        m = 1;
                    }
                }while (m);
            }
            printf("\n");
            for(i = 0; i < n; i++){
                xp[i] = mas_b[i]/mas_a[i][i];
                
            }
            float delta, prop, E, maxdelta;
            E = pow(10, -(toch));
            do{
                maxdelta = 0;
                for (i = 0; i < n; i++){
                    sum[i] = 0;
                    for(j = 0; j < n; j++){
                        if(j != i){
                            sum[i] = sum[i] + (mas_a[i][j] * xp[j]);
                        }
                    }
                }
                for (i = 0; i < n; i++){
                    x1[i] = (mas_b[i] - sum[i])/mas_a[i][i];
                    delta = fabs(x1[i] - xp[i]);
                    
                    if (delta > maxdelta){
                        maxdelta = delta;
                    }
                }
                for (i = 0; i < n; i++){
                    xp[i] = x1[i];
                }
                prop = maxdelta;
            }while (prop > E);
            for(i = 0; i < n; i++){
                printf("x[%d] = %g \n", i+1, x1[i]);
            }
        }
        for (int i = 0; i < n; i++)
        free(mas_a[i]);
        free(mas_a);
        free(mas_b);
        free(sum);
        free(x1);
        free(xp);
        printf ("Щоб закінчити програму, натисніть ESC!\n" "Якщо хочете ще раз скористатися, натисніть Enter\n");
    }   while (getch()!=27);
    return 0; 
}
