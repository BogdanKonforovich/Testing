#include <stdio.h>
#include <math.h>
#include <windows.h>
#define Size 1000

void Creatmas (int mas[], int n);
void Printmas (int mas[], int n);

int main() {

    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    int mas[Size], roz;
    char m, en;
    printf("Введіть розмір масиву: ");
    do {
        m = 0;
        if(scanf("%d%c", &roz, &en) != 2 || en != '\n'){
            m = 1;
            fflush(stdin);
            printf("Введіть розмір масиву в правильній формі (Приклад: 2) \nПовторіть спробу: ");
        }
        else {
            if (roz <= 0){
                m = 1;
                printf("Розмір масиву повинен бути більше 0! \nПовторіть спробу: ");
            }
        }
    } while (m);
    Creatmas(mas, roz);
    Printmas(mas, roz);
    system("pause");
    return 0;
}
void Creatmas (int mas[], int n){
    int i;
    for (i = 0; i < n; i++){
        mas[i] = i + 1;
    }
}

void Printmas (int mas[], int n){
    int i, j;
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            if (mas[i] == mas[j]*mas[j]){
                printf ("Число %d є квадратом числу %d \n", mas[i], mas[j]);
            }
        }
    }
}

