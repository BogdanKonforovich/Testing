#include <stdio.h>
#include <math.h>
#include <windows.h> 
#define Size 20
void Create1(char mas[],int n);
void Create2(char mas[],int n);
void Create3(char mas1[], char mas2[], char mas3[],int n);
void Per(char mas[], int n);
int Lin(char mas[], int n, char x);
int Binar(char mas[], int n, char x);

int main() {

    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    

char mas1[Size], mas2[Size], mas3[Size], sym;
int n, i;
printf("Введіть значення n (від 10 до 18) ");
scanf("%d", &n);
printf("\nВведіть символ, для якого шукаємо останнє подвоєння: ");

    scanf(" %c", &sym);
    printf("Масив №1 \n");
    Create1(mas1, n);
    printf("\nМасив №2 \n");
    Create2(mas2, n);
    printf("\nМасив №3 \n");
    Create3(mas1, mas2, mas3, n);
    Per(mas1, n);

    int pos1 = Lin(mas2, n, sym);
    if (pos1 != -1)
        printf("\nЛінійний пошук: останнє подвоєння '%c' починається з позиції %d\n", sym, pos1);
    else
        printf("\nЛінійний пошук: подвоєння '%c' не знайдено\n", sym);

    int pos2 = Binar(mas2, n, sym);
    if (pos2 != -1)
        printf("\nБінарний пошук: останнє подвоєння '%c' починається з позиції %d\n", sym, pos2);
    else
        printf("\nБінарний пошук: подвоєння '%c' не знайдено\n", sym);

    system("pause");
    return 0;
}
void Create1(char mas[],int n){
    int i;
    for (i = 0; i < n; i++){
        mas[i] = 120 - i;
        printf("%d, ", mas[i]);
    }
}
void Create2(char mas[],int n){
    int i;
    for (i = 0; i < n; i++){
        mas[i] = 110 + i;
        printf("%d, ", mas[i]);
    }
}

void Create3 ( char mas1[], char mas2[], char mas3[], int n){
    int i, j, k=0, num, m =0;

    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            if(mas1[i] == mas2[j]){
                mas3[k] = mas1[i];
                printf("%d, ", mas3[k]);
                num = (int)mas3[k];
                if(num < 115){
                    m++;
                }
                k++;
            }
        }
    }
    printf("\nКількість чисел мениших 115 доревнює %d\n", m);
}

void Per(char mas[], int n){
    int num, i, k, l, m, last;
    for (i = 0; i < n; i++){
        num = (int)mas[i];
        k = num/100;
        l = (num%100)/10;
        m = num%10;
        if (k == l || l == m){
            last = num;
        }
    }
    printf("\nОстанній подвоєний елемент першого масиву: %d\n", last);
}

int Lin(char mas[], int n, char x) {
    int lastPos = -1;
    for (int i = 0; i < n - 1; i++) {
        if (mas[i] == x && mas[i + 1] == x)
            lastPos = i;
    }
    return lastPos;
}

int Binar(char mas[], int n, char x) {
    int left = 0, right = n - 1, lastPos = -1;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (mas[mid] == x) {
            if (mid < n - 1 && mas[mid + 1] == x){
                lastPos = mid;
            }
            left = mid + 1;
        }
        else {if (mas[mid] < x){
            left = mid + 1;}
            else{
                right = mid - 1;}
        }
    }
    return lastPos;
}