#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#define min_r 2
#define min_s 1
#define max 10
#define max_2 11
#define per_k 50

void sort(char **mass, int num){
    int i, j;
    for(i = 0; i < num-1; i++)
        for(j = i+1; j < num; j++)
            if(strcmp(mass[i], mass[j]) > 0){
                char *tmp;
                tmp = mass[i];
                mass[i] = mass[j];
                mass[j] = tmp;
            }
}

int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    char mas[max][max_2] = {0}, m = 0, en, per[per_k];
    int r, s, i, j = 0, v;
    
    do{
        printf("Введіть кількість рядочків масиву (від %d до %d включно), не використовуючи експоненціальної форми: ", min_r, max);
        do {
            m = 0;
            if (scanf("%d%c", &r, &en) != 2 || en!='\n'){
                printf("Введіть число в правильній формі \nПовторіть спробу:");
                m = 1;
                while (getchar() != '\n');
            }
            else if (r < min_r || r > max){
                printf("Число не входить в заданий діапазон (від %d до %d включно) \nПовторіть спробу:", min_r, max);
                m = 1;
            }
        } while(m);
        printf("Введіть кількість стовпчиків масиву (від %d до %d включно), не використовуючи експоненціальної форми:", min_s, max);
        do {
            m = 0;
            if (scanf("%d%c", &s, &en) != 2 || en!='\n'){
                printf("Введіть число в правильній формі \nПовторіть спробу:");
                m = 1;
                while (getchar() != '\n');
            }
            else if (s < min_s || s > max){
                printf("Число не входить в заданий діапазон (від %d до %d включно) \nПовторіть спробу:", min_s, max);
                m = 1;
            }
        } while(m);
        
        for(i = 0; i < r && m == 0; i++){
            do{
            m = 0;
            j = 0;
            printf("%d)", i+1);
            fgets(per, per_k, stdin);
            while (per[j] != '\0' && per[j] != '\n'){
                j++;
            }
            if (j <= per_k){
                fflush(stdin);
            }
            if (j == 0){
                m = 1;
                printf("Рядок не може бути порожнім!\nПовторіть спробу\n");
            }
            if (j > s){
                m = 1;
                printf("Введено забагато символів (Повинно бути не більше %d) \nПовторіть спробу\n", s);
            }
            }while(m);
            per[j] = '\0';
            strcpy(mas[i], per);
        }
        char *addr[max];
        for(i = 0; i < r; i++) {
            addr[i] = mas[i];
        }
        sort(addr, r);
        printf("Оберіть спосіб сортування 1 - за зростанням, 0 - за спаданням\n");
        do {
            m = 0;
            if (scanf("%d%c", &v, &en) != 2 || en!='\n'){
                printf("Введіть число в правильній формі \nПовторіть спробу:");
                m = 1;
                while (getchar() != '\n');
            }else{
                if(v != 0 && v != 1){
                    printf("Ви ввели інше число! Введіть 1 або 0 \nПовторіть спробу:");
                    m = 1;
                }
            }
        }while (m);
        if (v == 1){
            printf("Відсортований масив:\n");
            for(i = 0; i < r; i++){
                printf("%d) %s\n", i+1, addr[i]);
            }
        }
        if (v == 0){
            printf("Відсортований масив:\n");
            for(i = r-1; i >= 0; i--, v++){
                printf("%d) %s\n", v+1, addr[i]);
            }
        }
        printf ("Щоб закінчити програму, натисніть ESC!\n" "Якщо хочете ще раз скористатися, натисніть Enter\n");
    }   while (getch()!=27);
    return 0; 
}