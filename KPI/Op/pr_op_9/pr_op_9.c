#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <string.h>

#define min 0
#define max 10
#define min_n 350
#define End ".dat"
#define max_s 1e8
#define min_s 1e-6
#define max_nas 1e9
#define min_nas 1.0
#define Per "myfile.dat"
#define min_num 1
#define max_num 1000
#define min_vpor 1
#define max_vpor 3
// #define SIGN_LEN 11   // довжина "myfile.dat" + '\0'

typedef struct rec {
    char name[min_n+2];
    float square;
    int nas;
} rec;
typedef struct zag {
    char sign[strlen(Per)+1];
    char sort_type;
    char sort_order;
} zag;

void per(int *n);

void create_f(FILE**fil, char *filename);

void create_zap(FILE**fil, char *filename);

void read_file(FILE**fil, char *filename);

void delete_f(FILE**fil, char *filename);

void read_z(FILE**fil, char *filename);

void redact_z(FILE**fil, char *filename);

void sort_z(FILE**fil, char *filename);

void vpor(FILE**fil, char *filename);

void delete_z(FILE**fil, char *filename);

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    FILE *fil;
    rec a;
    rec *add;
    char m = 0;
    char filename[min_n+2];
    strcpy(filename, "&&&&&");
    int n;
    do{
        printf("Файл\t\t Записи\n");
        printf("1 - Створити\t 4 - Створти\n");
        printf("2 - Зчитати\t 5 - Зчитати\n");
        printf("3 - Видалити\t 6 - Редагувати\n");
        printf("\t\t 7 - Впорядкувати\n");
        printf("\t\t 8 - Вставка\n");
        printf("\t\t 9 - Видалення\n");
        printf("\t\t 10 - Вихід\n");
        printf("\t\t 0 - Змінити файл\n");

        printf("\nВведіть номер дії (%d - %d): ", min, max);

        per(&n);
        if(n == 1){
            create_f(&fil, filename);
        }
        if(n == 2){
            read_file(&fil, filename);
        }
        if(n == 3){
            delete_f(&fil, filename);
        }
        if(n == 4){
            create_zap(&fil, filename);
        }
        if(n == 5){
            read_z(&fil, filename);
        }

        if(n == 6){
            redact_z(&fil, filename);
        }
        if(n == 7){
            sort_z(&fil, filename);
        }
        if(n == 8){
            vpor(&fil, filename);
        }
        if(n == 9){
            delete_z(&fil, filename);
        }
        if(n == 10){
            strcpy(filename, "&&&&&"); 
        }

        if(n == 0){
            strcpy(filename, "&&&&&"); 
            printf("Файл закрито. Оберіть настіпну дію, а потім назву файлу\n");
        }
    }while(n != 10);
    return 0;
}


void per(int *n){
    char en;
    int m;
    do{
        m = 0;
        if(scanf("%d%c", n, &en) != 2 || en != '\n'){
            printf ("Введіть число в правильній формі! (Тільки число)\nПовторіть спробу введення: ");
            m = 1;
            while (getchar() != '\n');
        }else if(*n < min || *n > max){
            printf ("Введене число не входить в заданий діапазон!\nПовторіть спробу введення: ");
            m = 1;
        }
    }
    while (m);
}

void create_f(FILE**fil, char *filename){
    printf("Введіть назву файлу: ");
    char c, fullname[min_n+6];
    int j;
    do{
        c = 0;
        j = 0;
        // fflush(stdin);
        fgets(filename, min_n+2, stdin);
            while (filename[j] != '\0' && filename[j] != '\n'){
                j++;
            }
            if(strcmp(filename, "&&&&&") == 0 || strcmp(filename, "/") == 0){
                printf("Оберіть іншу назву\n");
            }else{
                if(filename[j] == '\n'){
                    filename[j] = '\0';
                }
                if (j == 0){
                    c = 1;
                    printf("Ви не ввели назву файлу!\nПовторіть спробу\n");
                }
                if (j > min_n){
                    c = 1;
                    printf("Введено забагато символів (Повинно бути не більше %d) \nПовторіть спробу\n", min_n);
                    fflush(stdin);
                }
            if(!c){
                strcpy(fullname, filename);
                strcat(fullname, End);
                FILE *test = fopen(fullname, "rb");
                if(test != NULL){
                printf("Файл з такою назвою вже існує! Введіть іншу назву\n");
                fclose(test);
                c = 1;
                }else{
                    *fil = fopen(fullname, "wb");
                    if (*fil == NULL) {
                        printf("Не вдалося створити файл.\n");
                    }
                    else {
                        zag head;
                        head.sort_order = 0;
                        head.sort_type = 0;
                        strcpy(head.sign, Per);
                        int wnear;
                        if((wnear = fwrite(&head, sizeof(zag), 1, *fil)) != 1){
                            printf("Помилка створення файлу.\n");
                        }
                        else{
                            printf("Файл створено успішно.\n");
                        }
                        fclose(*fil);
                    }
                }
            }
        }
    }while(c);
}

void create_zap(FILE**fil, char *filename){
    rec a;
    char c, fullname[min_n+6], g = 0;
    int j;
    if(strcmp(filename, "&&&&&") == 0){
        printf("Введіть назву файлу для запису: ");
        do{
            c = 0;
            j = 0;
            // fflush(stdin);
            fgets(filename, min_n+2, stdin);
                while (filename[j] != '\0' && filename[j] != '\n'){
                    j++;
                }
                if(filename[j] == '\n'){
                    filename[j] = '\0';
                }
                if (j == 0){
                    c = 1;
                    printf("Ви не ввели назву файлу!\nПовторіть спробу\n");
                }
                if (j > min_n){
                    c = 1;
                    printf("Введено забагато символів (Повинно бути не більше %d) \nПовторіть спробу\n", min_n);
                    fflush(stdin);
                }    
            }while(c);
        }
        char v = 0;
        strcpy(fullname, filename);
        strcat(fullname, End);
        zag head;
        *fil = fopen(fullname, "rb");
        if (*fil == NULL) {
            printf("Не вдалося відкрити файл, перевірте існування цього файлу.\n");
            v = 1;
        }
        else{
            if(fread(&head, sizeof(zag), 1, *fil) != 1){
                printf("Не вдалося прочитати файл.\n");
                g = 1;
            }
            fclose(*fil);
            if(!g){
                if(strcmp(head.sign, Per) != 0){
                    printf("Файл з такою назвою ще не був створений\nОберіть інший файл\n");
                    v = 1;
                }
                if(!v){
                    *fil = fopen(fullname, "rb+");
                    if (*fil == NULL) {
                        printf("Не вдалося відкрити файл\n");
                    }
                    else {
                        printf("Файл відкрито успішно\n");
                        printf("Введіть назву міста\n");
                        do{
                        fflush(stdin);
                        fgets(a.name, min_n+2, stdin);
                        j = 0;
                        c = 0;
                        while (a.name[j] != '\0' && a.name[j] != '\n'){
                            j++;
                        }
                        if(a.name[j] == '\n'){
                            a.name[j] = '\0';
                        }
                        if(j == 0){
                            printf("Ви не ввели назву міста!\n");
                            c = 1;
                        }
                        if(j > min_n){
                            printf("Введено забагато символів (Повинно бути не більше %d) \n", min_n);
                            c = 1;
                            fflush(stdin);
                        }
                    }while (c);
                    printf("Введіть площу міста (від %g до %g, 0 також підходить): ", min_s, max_s);  
                        char en;
                        do{
                            c = 0;
                            if(scanf("%f%c", &a.square, &en) != 2 || en != '\n'){
                                printf ("Введіть число в правильній формі! (Тільки число)\nПовторіть спробу введення: ");
                                c = 1;
                                while (getchar() != '\n');
                            }else if((a.square < min_s && a.square!=0) || a.square > max_s){
                                printf ("Введене число не входить в заданий діапазон!\nПовторіть спробу введення: ");
                                c = 1;
                            }
                        }
                        while (c);
                    printf("Введіть населення міста (від %g до %g): ", min_nas, max_nas);
                    do{
                        c = 0;
                        if(scanf("%d%c", &a.nas, &en) != 2 || en != '\n'){
                            printf ("Введіть число в правильній формі! (Тільки число)\nПовторіть спробу введення: ");
                            c = 1;
                            while (getchar() != '\n');
                        }else if(a.nas < min_nas || a.nas > max_nas){
                            printf ("Введене число не входить в заданий діапазон!\nПовторіть спробу введення: ");
                            c = 1;
                        }
                    }while(c);
                int nwrite;
                fseek(*fil, 0, SEEK_END);
                nwrite = fwrite(&a, sizeof(rec), 1, *fil);
                if(nwrite != 1){
                    printf("Помилка запису в файл.\n");
                }else{
                    printf("Запис додано успішно.\n");
                    fseek(*fil, 0, SEEK_SET);
                    head.sort_order = 0;
                    head.sort_type = 0;
                    strcpy(head.sign, Per);
                    if(fwrite(&head, sizeof(zag), 1, *fil) != 1){
                    printf("Помилка оновлення заголовку!\n");
                }
                }
                fclose(*fil);
                }
            }
        }
    }
}

void read_file(FILE**fil, char *filename){
    char c, fullname[min_n+6];
    int j;
        c = 0;
        j = 0;
        // fflush(stdin);
        if(strcmp(filename, "&&&&&") == 0){
            printf("Введіть назву файлу для зчитування: ");
            do{
            fgets(filename, min_n+2, stdin);
            while (filename[j] != '\0' && filename[j] != '\n'){
                j++;
            }
            if(filename[j] == '\n'){
                filename[j] = '\0';
            }
            if (j == 0){
                c = 1;
                printf("Ви не ввели назву файлу!\nПовторіть спробу\n");
            }
            if (j > min_n){
                c = 1;
                printf("Введено забагато символів (Повинно бути не більше %d) \nПовторіть спробу\n", min_n);
                fflush(stdin);
            }
        }while (c);
    }
        char v = 0;
        strcpy(fullname, filename);
        strcat(fullname, End);
        zag head;
        *fil = fopen(fullname, "rb");
        if(fread(&head, sizeof(zag), 1, *fil) != 1){
            printf("Не вдалося прочитати файл, перевірте існування цього файлу\n");
            v = 1;
        }
        fclose(*fil);
        if(!v){
            if(strcmp(head.sign, Per) != 0){
                printf("Файл з такою назвою ще не був створений\nОберіть інший файл\n");
                v = 1;
            }
        if(!v){
            *fil = fopen(fullname, "rb");
            if(*fil == NULL){
                printf("Не вдалося відкрити файл\n");
            }else{
                printf("Файл відкрито успішно.\n");
                rec a;

                    // пропускаємо сигнатуру
                    // fseek переміщує курсору файлу на певну кількість байтів.
                    // strlen(Per) = 11 (довжина "myfile.dat").
                    // SEEK_SET = початок файлу.

                fseek(*fil, sizeof(zag), SEEK_SET);
                int num = 1;
                while(fread(&a, sizeof(rec), 1, *fil) == 1){
                    printf("%d)Місто: %s \nПлоща: %g \nНаселення: %d\n",num, a.name, a.square, a.nas);
                    num++;
                }
                if(num == 1){
                    printf("Файл порожній!\n");
                }
                fclose(*fil);
            }
        }
    }
}


void delete_f(FILE**fil, char *filename){
    char c, fullname[min_n+6];
    int j;
    if(strcmp(filename, "&&&&&") == 0){
        printf("Введіть назву файлу для видалення: ");
        do{
            c = 0;
            j = 0;
            // fflush(stdin);
            fgets(filename, min_n+2, stdin);
            while (filename[j] != '\0' && filename[j] != '\n'){
                j++;
            }
            if(filename[j] == '\n'){
                filename[j] = '\0';
            }
            if (j == 0){
                c = 1;
                printf("Ви не ввели назву файлу!\nПовторіть спробу\n");
            }
            if (j > min_n){
                c = 1;
                printf("Введено забагато символів (Повинно бути не більше %d) \nПовторіть спробу\n", min_n);
                fflush(stdin);
            }
        }while (c);
    }
        char v = 0;
        strcpy(fullname, filename);
        strcat(fullname, End);
        zag head;
        *fil = fopen(fullname, "rb");
        if(fread(&head, sizeof(zag), 1, *fil) != 1){
            printf("Не вдалося прочитати файл, перевірте існування цього файлу\n");
            v = 1;
        }
        fclose(*fil);
        if(!v){
            if(strcmp(head.sign, Per) != 0){
                printf("Файл з такою назвою ще не був створений\nОберіть інший файл\n");
                v = 1;
            }
        if(!v){
            if (remove(fullname) == 0){ // якщо -1 файл не видалено
                printf("Файл видалено успішно.\n");
                strcpy(filename, "&&&&&");
            }else{
                printf("Не вдалося видалити файл.\n");
            }
        }
    }
}

void read_z(FILE**fil, char *filename){
    
    char c, fullname[min_n+6];
    int j;
    if(strcmp(filename, "&&&&&") == 0){
        printf("Введіть назву файлу для зчитування: ");
        do{
            c = 0;
            j = 0;
            // fflush(stdin);
            fgets(filename, min_n+2, stdin);
            while (filename[j] != '\0' && filename[j] != '\n'){
                j++;
            }
            if(filename[j] == '\n'){
                filename[j] = '\0';
            }
            if (j == 0){
                c = 1;
                printf("Ви не ввели назву файлу!\nПовторіть спробу\n");
            }
            if (j > min_n){
                c = 1;
                printf("Введено забагато символів (Повинно бути не більше %d) \nПовторіть спробу\n", min_n);
                fflush(stdin);
            }
        }while (c);
    }
        char v = 0;
        strcpy(fullname, filename);
        strcat(fullname, End);
        zag head;
        *fil = fopen(fullname, "rb");
        if(fread(&head, sizeof(zag), 1, *fil) != 1){
            printf("Не вдалося прочитати файл, перевірте існування цього файлу\n");
            v = 1;
        }
        fclose(*fil);
        if(!v){
            if(strcmp(head.sign, Per) != 0){
                printf("Файл з такою назвою ще не був створений\nОберіть інший файл\n");
                v = 1;
            }
        if(!v){
            *fil = fopen(fullname, "rb");
            if(*fil == NULL){
                printf("Не вдалося відкрити файл\n");
            }else{
                printf("Файл відкрито успішно.\n");
                rec a;

                    // пропускаємо сигнатуру
                    // fseek переміщує курсору файлу на певну кількість байтів.
                    // strlen(Per) = 11 (довжина "myfile.dat").
                    // SEEK_SET = початок файлу.

                fseek(*fil, sizeof(zag), SEEK_SET);
                if(fread(&a, sizeof(rec), 1, *fil) != 1){
                    printf("Файл порожній!\n");
                    fclose(*fil);
                } else{
                    fseek(*fil, sizeof(zag), SEEK_SET);
                    int num_v = 1;
                    char l, en;
                    printf("Введіть номер запису:");
                    do {
                        l = 0;
                        if(scanf("%d%c", &num_v, &en) != 2 || en != '\n'){
                            printf("Введіть значення в правильній формі (Наприклад 21) \nПовторіть спробу:");
                            while (getchar() != '\n');
                            l = 1;
                        } else {
                        if (num_v < min_num){
                            printf ("Номер повинен бути більше %d \nПовторіть спробу:", min_num-1);
                            l = 1;
                        }
                        }
                    } while (l);
                    int num = 1;
                    char b = 0;
                    while(fread(&a, sizeof(rec), 1, *fil) == 1 && b == 0){
                        if(num == num_v){
                            printf("%d)Місто: %s \nПлоща: %g \nНаселення: %d\n",num, a.name, a.square, a.nas);
                            b = 1;
                        }
                        if(!b){
                            num++;
                        }
                    }
                    if(num == 1){
                        printf("Файл порожній!\n");
                    }
                    if(num < num_v){ 
                        printf("Запису з таким номером не існує (максимальний номер %d)\n", num);
                    }
                    fclose(*fil);
                }
            }
        }
    }
}

void redact_z(FILE**fil, char *filename){
    
    char c, fullname[min_n+6];
    int j;
    if(strcmp(filename, "&&&&&") == 0){
        printf("Введіть назву файлу для редагування: ");
        do{
            c = 0;
            j = 0;
            // fflush(stdin);
            fgets(filename, min_n+2, stdin);
            while (filename[j] != '\0' && filename[j] != '\n'){
                j++;
            }
            if(filename[j] == '\n'){
                filename[j] = '\0';
            }
            if (j == 0){
                c = 1;
                printf("Ви не ввели назву файлу!\nПовторіть спробу\n");
            }
            if (j > min_n){
                c = 1;
                printf("Введено забагато символів (Повинно бути не більше %d) \nПовторіть спробу\n", min_n);
                fflush(stdin);
            }
        }while (c);
    }
        char v = 0;
        strcpy(fullname, filename);
        strcat(fullname, End);
        zag head;
        *fil = fopen(fullname, "rb");
        if(fread(&head, sizeof(zag), 1, *fil) != 1){
            printf("Не вдалося прочитати файл, перевірте існування цього файлу\n");
            v = 1;
        }
        fclose(*fil);
        if(!v){
            if(strcmp(head.sign, Per) != 0){
                printf("Файл з такою назвою ще не був створений\nОберіть інший файл\n");
                v = 1;
            }
        if(!v){
            *fil = fopen(fullname, "r+b");
            if(*fil == NULL){
                printf("Не вдалося відкрити файл\n");
            }else{
                printf("Файл відкрито успішно.\n");
                rec a;

                    // пропускаємо сигнатуру
                    // fseek переміщує курсору файлу на певну кількість байтів.
                    // strlen(Per) = 11 (довжина "myfile.dat").
                    // SEEK_SET = початок файлу.

                fseek(*fil, sizeof(zag), SEEK_SET);
                int num_v = 1;
                char l, en;
                printf("Введіть номер запису:");
                do {
                    l = 0;
                    if(scanf("%d%c", &num_v, &en) != 2 || en != '\n'){
                        printf("Введіть значення в правильній формі (Наприклад 21) \nПовторіть спробу:");
                        while (getchar() != '\n');
                        l = 1;
                    } else {
                    if (num_v < min_num){
                        printf ("Номер повинен бути більше %d \nПовторіть спробу:", min_num-1);
                        l = 1;
                    }
                    }
                } while (l);
                int num = 1;
                while(fread(&a, sizeof(rec), 1, *fil) == 1 && num < num_v){
                    num++;
                }
                if(num == num_v){
                    fseek(*fil, -sizeof(rec), SEEK_CUR);
                    printf("Введіть назву міста\n");
                    do{
                    fflush(stdin);
                    fgets(a.name, min_n+2, stdin);
                    j = 0;
                    c = 0;
                    while (a.name[j] != '\0' && a.name[j] != '\n'){
                        j++;
                    }
                    if(a.name[j] == '\n'){
                        a.name[j] = '\0';
                    }
                    if(j == 0){
                        printf("Ви не ввели назву міста!\n");
                        c = 1;
                    }
                    if(j > min_n){
                        printf("Введено забагато символів (Повинно бути не більше %d) \n", min_n);
                        c = 1;
                        fflush(stdin);
                    }
                }while (c);
                printf("Введіть площу міста (від %g до %g, 0 також підходить): ", min_s, max_s);  
                    do{
                        c = 0;
                        if(scanf("%f%c", &a.square, &en) != 2 || en != '\n'){
                            printf ("Введіть число в правильній формі! (Тільки число)\nПовторіть спробу введення: ");
                            c = 1;
                            while (getchar() != '\n');
                        }else if((a.square < min_s && a.square!=0) || a.square > max_s){
                            printf ("Введене число не входить в заданий діапазон!\nПовторіть спробу введення: ");
                            c = 1;
                        }
                    }
                    while (c);
                printf("Введіть населення міста (від %g до %g): ", min_nas, max_nas);
                do{
                        c = 0;
                        if(scanf("%d%c", &a.nas, &en) != 2 || en != '\n'){
                            printf ("Введіть число в правильній формі! (Тільки число)\nПовторіть спробу введення: ");
                            c = 1;
                            while (getchar() != '\n');
                        }else if(a.nas < min_nas || a.nas > max_nas){
                            printf ("Введене число не входить в заданий діапазон!\nПовторіть спробу введення: ");
                            c = 1;
                        }
                    }while(c);
                int nwrite;
                nwrite = fwrite(&a, sizeof(rec), 1, *fil);
                if(nwrite != 1){
                    printf("Помилка запису в файл.\n");
                }else{
                    printf("Запис змінено успішно.\n");
                }
                } else {
                    printf("Запису з таким номером не існує (максимальний номер %d)\n", num);
                }
                fseek(*fil, 0, SEEK_SET);
                head.sort_order = 0;
                head.sort_type = 0;
                strcpy(head.sign, Per);
                if(fwrite(&head, sizeof(zag), 1, *fil) != 1){
                    printf("Помилка оновлення заголовку!\n");
                }
            fclose(*fil);
            }
        }
    }
}

void sort_z(FILE**fil, char *filename){
    
    char c, fullname[min_n+6];
    int j;
    if(strcmp(filename, "&&&&&") == 0){
        printf("Введіть назву файлу для сортування: ");
        do{
            c = 0;
            j = 0;
            // fflush(stdin);
            fgets(filename, min_n+2, stdin);
            while (filename[j] != '\0' && filename[j] != '\n'){
                j++;
            }
            if(filename[j] == '\n'){
                filename[j] = '\0';
            }
            if (j == 0){
                c = 1;
                printf("Ви не ввели назву файлу!\nПовторіть спробу\n");
            }
            if (j > min_n){
                c = 1;
                printf("Введено забагато символів (Повинно бути не більше %d) \nПовторіть спробу\n", min_n);
                fflush(stdin);
            }
        }while (c);
    }
        char v = 0;
        strcpy(fullname, filename);
        strcat(fullname, End);
        zag head;
        *fil = fopen(fullname, "rb");
        if(fread(&head, sizeof(zag), 1, *fil) != 1){
            printf("Не вдалося прочитати файл, перевірте існування цього файлу\n");
            v = 1;
        }
        fclose(*fil);
        if(!v){
            if(strcmp(head.sign, Per) != 0){
                printf("Файл з такою назвою ще не був створений\nОберіть інший файл\n");
                v = 1;
            }
        if(!v){
            *fil = fopen(fullname, "r+b");
            if(*fil == NULL){
                printf("Не вдалося відкрити файл\n");
            }else{
                printf("Файл відкрито успішно\n");
                fseek(*fil, sizeof(zag), SEEK_SET);
                rec a;
                int count = 0;
                while(fread(&a, sizeof(rec), 1, *fil) == 1){
                    count++;
                }
                if(count < 2){
                    printf("Недостатньо записів для сортування!\n");
                }else{
                    rec* mas = (rec*)malloc(count * sizeof(rec));
                    if (mas == NULL){
                        printf("Помилка виділення пам'яті!\n");
                    }else{
                        fseek(*fil, sizeof(zag), SEEK_SET);
                        for(int i = 0; i < count; i++){
                            fread(&mas[i], sizeof(rec), 1, *fil);
                        }
                        printf("1 - впорядкувати за назвою міста\n2 - впорядкувати за площею міста\n3 - впорядкувати за населенням міста\n");
                        int num;
                        char en;
                        do{
                            c = 0;
                            printf("Введіть номер дії: ");
                            if(scanf("%d%c", &num, &en) != 2 || en != '\n'){
                                printf ("Введіть число в правильній формі! (Тільки число)\nПовторіть спробу введення: ");
                                c = 1;
                                while (getchar() != '\n');
                            }else if(num < min_vpor || num > max_vpor){
                                printf ("Введене число не входить в заданий діапазон!\nПовторіть спробу введення: ");
                                c = 1;
                            }
                        }while(c);
                        if(num == 1){
                            for(int i = 0; i < count-1; i++){
                                for(j = 0; j < count-i-1; j++){
                                    if(strcmp(mas[j].name, mas[j+1].name) > 0){
                                        rec temp = mas[j];
                                        mas[j] = mas[j+1];
                                        mas[j+1] = temp;
                                    }
                                }
                            }
                        }
                        if(num == 2){
                            for(int i = 0; i < count-1; i++){
                                for(j = 0; j < count-i-1; j++){
                                    if(mas[j].square > mas[j+1].square){
                                        rec temp = mas[j];
                                        mas[j] = mas[j+1];
                                        mas[j+1] = temp;
                                    }
                                }
                            }
                        }
                        if(num == 3){
                            for(int i = 0; i < count-1; i++){
                                for(j = 0; j < count-i-1; j++){
                                    if(mas[j].nas > mas[j+1].nas){
                                        rec temp = mas[j];
                                        mas[j] = mas[j+1];
                                        mas[j+1] = temp;
                                    }
                                }
                            }
                        }
                        printf("1 - за зростанням\n2 - за спаданням\n");
                        int num2;
                        do{
                            c = 0;
                            printf("Введіть номер дії: ");
                            if(scanf("%d%c", &num2, &en) != 2 || en != '\n'){
                                printf ("Введіть число в правильній формі! (Тільки число)\nПовторіть спробу введення: ");
                                c = 1;
                                while (getchar() != '\n');
                            }else if(num2 < min_vpor || num2 > max_vpor-1){
                                printf ("Введене число не входить в заданий діапазон!\nПовторіть спробу введення: ");
                                c = 1;
                            }
                        }while(c);
                        fseek(*fil, sizeof(zag), SEEK_SET);
                        char k = 0;
                        if(num2 == 1){
                            for(int i = 0; i < count; i++){
                                if(fwrite(&mas[i], sizeof(rec), 1, *fil) != 1){
                                    printf("Помилка запису в файл.\n");
                                    k = 1;
                                }
                            }
                        }else{
                            for(int i = count-1; i >= 0; i--){
                                if(fwrite(&mas[i], sizeof(rec), 1, *fil) != 1){
                                    printf("Помилка запису в файл.\n");
                                    k = 1;
                                }
                            }
                        }
                        if(!k){
                            printf("Файл впорядковано успішно\n");
                            fseek(*fil, 0, SEEK_SET);
                            head.sort_type = num;   // 1,2,3
                            head.sort_order = num2; // 1,2
                            if(fwrite(&head, sizeof(zag), 1, *fil) != 1){
                                printf("Помилка оновлення заголовку!\n");
                            }                       
                        }
                        free(mas);
                    }
            }
            fclose(*fil);
            }
        }
    }
}

void vpor(FILE**fil, char *filename){
    
    char c, fullname[min_n+6];
    int j;
    if(strcmp(filename, "&&&&&") == 0){
        printf("Введіть назву файлу для вставки: ");
        do{
            c = 0;
            j = 0;
            // fflush(stdin);
            fgets(filename, min_n+2, stdin);
            while (filename[j] != '\0' && filename[j] != '\n'){
                j++;
            }
            if(filename[j] == '\n'){
                filename[j] = '\0';
            }
            if (j == 0){
                c = 1;
                printf("Ви не ввели назву файлу!\nПовторіть спробу\n");
            }
            if (j > min_n){
                c = 1;
                printf("Введено забагато символів (Повинно бути не більше %d) \nПовторіть спробу\n", min_n);
                fflush(stdin);
            }
        }while (c);
    }
    char v = 0;
    strcpy(fullname, filename);
    strcat(fullname, End);
    zag head;
    rec a;
    *fil = fopen(fullname, "rb");
    if(fread(&head, sizeof(zag), 1, *fil) != 1){
        printf("Не вдалося прочитати файл, перевірте існування цього файлу\n");
        v = 1;
    }
    fclose(*fil);
    if(!v){
        if(strcmp(head.sign, Per) != 0){
            printf("Файл з такою назвою ще не був створений\nОберіть інший файл\n");
            v = 1;
        }
        if(!v){
            *fil = fopen(fullname, "r+b");
            if(*fil == NULL){
                printf("Не вдалося відкрити файл\n");
            }else{
                printf("Файл відкрито успішно\n");
                if(fread(&head, sizeof(zag), 1, *fil) != 1){
                    printf("Не вдалося прочитати файл\n");
                    v = 1;
                } else {
                    if(head.sort_type == 0 || head.sort_order == 0){
                        printf("Файл не впорядковано раніше. Спочатку впорядкуйте файл\n");
                        v = 1;
                    }
                }
                if(!v){
                    int count = 0;
                    fseek(*fil, sizeof(zag), SEEK_SET);
                    while(fread(&a, sizeof(rec), 1, *fil) == 1){
                        count++;
                    }
                    rec* mas = (rec*)malloc((count+1) * sizeof(rec));
                    if (mas == NULL){
                        printf("Помилка виділення пам'яті!\n");
                    }else{
                        fseek(*fil, sizeof(zag), SEEK_SET);
                        for(int i = 0; i < count; i++){
                            fread(&mas[i], sizeof(rec), 1, *fil);
                        }
                    char c = 0, en;
                    printf("Введіть назву міста\n");
                    do{
                        fflush(stdin);
                        fgets(a.name, min_n+2, stdin);
                        j = 0;
                        c = 0;
                        while (a.name[j] != '\0' && a.name[j] != '\n'){
                            j++;
                        }
                        if(a.name[j] == '\n'){
                            a.name[j] = '\0';
                        }
                        if(j == 0){
                            printf("Ви не ввели назву міста!\n");
                            c = 1;
                        }
                        if(j > min_n){
                            printf("Введено забагато символів (Повинно бути не більше %d) \n", min_n);
                            c = 1;
                            fflush(stdin);
                        }
                    }while (c);
                    printf("Введіть площу міста (від %g до %g, 0 також підходить): ", min_s, max_s);  
                        do{
                            c = 0;
                            if(scanf("%f%c", &a.square, &en) != 2 || en != '\n'){
                                printf ("Введіть число в правильній формі! (Тільки число)\nПовторіть спробу введення: ");
                                c = 1;
                                while (getchar() != '\n');
                            }else if((a.square < min_s && a.square!=0) || a.square > max_s){
                                printf ("Введене число не входить в заданий діапазон!\nПовторіть спробу введення: ");
                                c = 1;
                            }
                        }
                        while (c);
                    printf("Введіть населення міста (від %g до %g): ", min_nas, max_nas);
                    do{
                        c = 0;
                        if(scanf("%d%c", &a.nas, &en) != 2 || en != '\n'){
                            printf ("Введіть число в правильній формі! (Тільки число)\nПовторіть спробу введення: ");
                            c = 1;
                            while (getchar() != '\n');
                        }else if(a.nas < min_nas || a.nas > max_nas){
                            printf ("Введене число не входить в заданий діапазон!\nПовторіть спробу введення: ");
                            c = 1;
                        }
                    }while(c);
                    mas[count] = a;
                    count++;
                            fseek(*fil, sizeof(zag), SEEK_SET);
                            int num = head.sort_type;
                            int num2 = head.sort_order;
                            if(num == 1){
                                for(int i = 0; i < count-1; i++){
                                    for(j = 0; j < count-i-1; j++){
                                        if(strcmp(mas[j].name, mas[j+1].name) > 0){
                                            rec temp = mas[j];
                                            mas[j] = mas[j+1];
                                            mas[j+1] = temp;
                                        }
                                    }
                                }
                            }
                            if(num == 2){
                                for(int i = 0; i < count-1; i++){
                                    for(j = 0; j < count-i-1; j++){
                                        if(mas[j].square > mas[j+1].square){
                                            rec temp = mas[j];
                                            mas[j] = mas[j+1];
                                            mas[j+1] = temp;
                                        }
                                    }
                                }
                            }
                            if(num == 3){
                                for(int i = 0; i < count-1; i++){
                                    for(j = 0; j < count-i-1; j++){
                                        if(mas[j].nas > mas[j+1].nas){
                                            rec temp = mas[j];
                                            mas[j] = mas[j+1];
                                            mas[j+1] = temp;
                                        }
                                    }
                                }
                            }
                            int k = 0;
                            if(num2 == 1){
                                for(int i = 0; i < count; i++){
                                    if(fwrite(&mas[i], sizeof(rec), 1, *fil) != 1){
                                        printf("Помилка запису в файл.\n");
                                        k = 1;
                                    }
                                }
                            }else{
                                for(int i = count-1; i >= 0; i--){
                                    if(fwrite(&mas[i], sizeof(rec), 1, *fil) != 1){
                                        printf("Помилка запису в файл.\n");
                                        k = 1;
                                    }
                                }
                            }
                            if(!k){
                                printf("Файл впорядковано успішно\n");
                                fseek(*fil, 0, SEEK_SET);
                                if(fwrite(&head, sizeof(zag), 1, *fil) != 1){
                                    printf("Помилка оновлення заголовку!\n");
                                }                       
                            }
                        free(mas);
                        }
                    }       
                fclose(*fil);
                }
            }
        } 
}

void delete_z(FILE**fil, char *filename){
    char c, fullname[min_n+6];
    int j;
    if(strcmp(filename, "&&&&&") == 0){
        printf("Введіть назву файлу для видалення запису: ");
        do{
            c = 0;
            j = 0;
            // fflush(stdin);
            fgets(filename, min_n+2, stdin);
            while (filename[j] != '\0' && filename[j] != '\n'){
                j++;
            }
            if(filename[j] == '\n'){
                filename[j] = '\0';
            }
            if (j == 0){
                c = 1;
                printf("Ви не ввели назву файлу!\nПовторіть спробу\n");
            }
            if (j > min_n){
                c = 1;
                printf("Введено забагато символів (Повинно бути не більше %d) \nПовторіть спробу\n", min_n);
                fflush(stdin);
            }
        }while (c);
    }
        char v = 0;
        strcpy(fullname, filename);
        strcat(fullname, End);
        zag head;
        *fil = fopen(fullname, "rb");
        if(fread(&head, sizeof(zag), 1, *fil) != 1){
            printf("Не вдалося прочитати файл, перевірте існування цього файлу\n");
            v = 1;
        }
        fclose(*fil);
        if(!v){
            if(strcmp(head.sign, Per) != 0){
                printf("Файл з такою назвою ще не був створений\nОберіть інший файл\n");
                v = 1;
            }
        if(!v){
            *fil = fopen(fullname, "r+b");
            if(*fil == NULL){
                printf("Не вдалося відкрити файл\n");
            }else{
                printf("Файл відкрито успішно.\n");
                rec a;

                    // пропускаємо сигнатуру
                    // fseek переміщує курсору файлу на певну кількість байтів.
                    // strlen(Per) = 11 (довжина "myfile.dat").
                    // SEEK_SET = початок файлу.

                fseek(*fil, sizeof(zag), SEEK_SET);
                int num_v = 1;
                char l, en;
                printf("Введіть номер запису для видалення:");
                do {
                    l = 0;
                    if(scanf("%d%c", &num_v, &en) != 2 || en != '\n'){
                        printf("Введіть значення в правильній формі (Наприклад 21) \nПовторіть спробу:");
                        while (getchar() != '\n');
                        l = 1;
                    } else {
                    if (num_v < min_num){
                        printf ("Номер повинен бути більше %d \nПовторіть спробу:", min_num-1);
                        l = 1;
                    }
                    }
                } while (l);
                int count = 0;
                fseek(*fil, sizeof(zag), SEEK_SET);
                while(fread(&a, sizeof(rec), 1, *fil) == 1){
                    count++;
                }
                if(num_v > count){
                    printf("Запису з таким номером не існує (максимальний номер %d)\n", count);
                }else{
                    rec* mas = (rec*)malloc((count-1) * sizeof(rec));
                    if (mas == NULL){
                        printf("Помилка виділення пам'яті!\n");
                    }else{
                        fseek(*fil, sizeof(zag), SEEK_SET);
                        int ind = 0;
                        for(int i = 0; i < count; i++){
                            fread(&a, sizeof(rec), 1, *fil);
                            if(i != num_v - 1){
                                mas[ind] = a;
                                ind++;
                            }
                        }
                        fclose(*fil);
                        fopen(fullname, "wb");
                        fseek(*fil, sizeof(zag), SEEK_SET);
                        int k = 0;
                        for(int i = 0; i < count-1; i++){
                            if(fwrite(&mas[i], sizeof(rec), 1, *fil) != 1){
                                printf("Помилка запису в файл.\n");
                                k = 1;
                            }
                        }
                        if(!k){
                            printf("Запис видалено успішно.\n");
                            fseek(*fil, 0, SEEK_SET);
                            head.sort_order = 0;
                            head.sort_type = 0;
                            if(fwrite(&head, sizeof(zag), 1, *fil) != 1){
                                printf("Помилка оновлення заголовку!\n");
                            }                       
                        }
                        free(mas);
                    }
                }
            }
            fclose(*fil);
        }
    }
}