#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <windows.h>

#define RED     "\033[31m"
#define GREEN   "\033[1m\033[32m"
#define RESET   "\033[0m"
#define min_n 1
#define max_n 4
#define min_r 1e-6
#define max_r 1e4
#define steps 1000
#define Pi 3.141592653589793
#define max_p 1e15

typedef struct zmin {
    double re;
    double im;
}complex;

float per(float x, float min, float max);

void kont1_2(complex *z,float R1, float L, float C, float Fmin, float Fmax, float Step, int num);

void kont3 (complex *z,float R1, float R2, float L, float C, float Fmin, float Fmax, float Step);

void kont4 (complex *z,float R1, float R2, float L, float C, float Fmin, float Fmax, float Step);

int main() {
complex z;
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    
    int num;
    float r1, r2, l, c, fmin, fmax, step = 0, pers;
    char m, en;
    
    do{
        printf("Введіть номер контуру (%d - %d) :", min_n, max_n);
        do{
            m = 0;
            if(scanf("%d%c", &num, &en) != 2 || en != '\n'){
                printf (RED "Введіть число в правильній формі! (Тільки число)\n" RESET "Повторіть спробу введення: ");
                m = 1;
                while (getchar() != '\n');
            }else if(num < min_n || num > max_n){
                printf (RED "Ви ввели інше число!\n" RESET "Повторіть спробу введення: ");
                m = 1;
            }
        }
        while (m);
        if (num == 1 || num == 2){
        printf("Введіть R (Om) (від %g до %g): ", min_r, max_r);
        r1 = per(r1, min_r, max_r);
        }
        
        if (num == 3 || num == 4){
            printf("Введіть R1 (Om) (від %g до %g): ", min_r, max_r);
            r1 = per(r1, min_r, max_r);
            printf("Введіть R2 (Om) (від %g до %g): ", min_r, max_r);
            r2 = per(r2, min_r, max_r);
        }
        printf("Введіть L (мГн) (від %g до %g): ", min_r, max_r);
        l = per(l, min_r, max_r);

        printf("Введіть C (мкФ) (від %g до %g): ", min_r, max_r);
        c = per(c, min_r, max_r);

        do{
            m = 0;
            printf("Введіть f min (від %g до %g): ", min_r, max_r);
            fmin = per(fmin, min_r, max_r);

            printf("Введіть f max (від %g до %g): ", fmin, max_r);
            fmax = per(fmax, min_r, max_r);
            if(fmin > fmax){
                printf(RED "fmin повинно бути меншим або дорівнювати fmax\n" RESET);
                m = 1;
            }
            if(!m && fmin < fmax){
                printf("Введіть Крок (від %g до %g): ", min_r, max_r);
                step = per(step, min_r, max_r);
                pers = (fmin + fmax)/step;
                if (steps < pers){
                    m = 1;
                    printf("Занадто багато кроків (%g) (Максимум %g). Збільшіть крок або зменшіть f max.\n", pers, steps);
                }
            }
        }
        while (m);
        
        if (num == 1 || num == 2){
            kont1_2(&z, r1, l, c, fmin, fmax, step, num);
        }

        if (num == 3)
        kont3(&z, r1, r2, l, c, fmin, fmax, step);

        if (num == 4)
        kont4(&z, r1, r2, l, c, fmin, fmax, step);

        printf ("Щоб закінчити програму, натисніть ESC!\n" "Якщо хочете ще раз скористатися, натисніть Enter\n");
    }   while (getch()!=27);
    return 0; 
}


float per(float x, float min, float max){
    char en;
    int m;
    do{
        m = 0;
        if(scanf("%f%c", &x, &en) != 2 || en != '\n'){
            printf (RED "Введіть число в правильній формі! (Тільки число)\n" RESET "Повторіть спробу введення: ");
            m = 1;
            while (getchar() != '\n');
        }else if(x < min || x > max){
            printf (RED "Введене число не входить в заданий діапазон!\n" RESET "Повторіть спробу введення: ");
            m = 1;
        }
    }
    while (m);
    return x;
}

void kont1_2(complex *z,float R1, float L, float C, float Fmin, float Fmax, float Step, int num){
    double a, b, d, f, f0, w;
    f0 = 1.0 / (2.0 * Pi * sqrt(L * C));
    printf("f0 = %g\n", f0);
    a = L/C;
    for (f = Fmin; f < Fmax; f = f + Step){
        w = 2* Pi * f;
        if (num == 1)
            b = -(R1/(w*C));
        else
            b = (R1/(w*C));
        d = w*L - 1.0/(w*C);
        z->re = (a*R1 + b*d)/(R1*R1 + d*d);
        z->im = (b*R1 - a*d)/(R1*R1 + d*d);
        printf("f = %g\t Z = %g + i*%g\n", f, z->re, z->im);
    }   
    if (round(f * max_r) >= round(Fmax * max_r)){
        f = Fmax;
        w = 2* Pi * f;
        if (num == 1)
            b = -(R1/(w*C));
        else
            b = (R1/(w*C));
        d = w*L - 1.0/(w*C);
        z->re = (a*R1 + b*d)/(R1*R1 + d*d);
        z->im = (b*R1 - a*d)/(R1*R1 + d*d);
        printf("f = %g\t Z = %g + i*%g\n", f, z->re, z->im);   
    }
}

void kont3 (complex *z,float R1, float R2, float L, float C, float Fmin, float Fmax, float Step){
    double a, b, c, d, f, f0, w;
    f0 = 1.0 / (2.0 * Pi * sqrt(L * C));
    printf("f0 = %g\n", f0);
    a = R1 * R2;
    c = R1 + R2;
    for (f = Fmin; f < Fmax; f = f + Step){
        w = 2* Pi * f;
        b = R1*(w*L - (1/(w*C)));
        d = w*L - (1/(w *C));
        z->re = (a*c + b*d)/(c*c + d*d);
        z->im = (b*c - a*d)/(c*c + d*d);
        printf("f = %g\t Z = %g + i*%g\n", f, z->re, z->im);
    }
    if(round(f * max_r) >= round(Fmax * max_r)){
        f = Fmax;
        w = 2* Pi * f;
        b = R1*(w*L - (1/(w*C)));
        d = w*L - (1/(w*C));
        z->re = (a*c + b*d)/(c*c + d*d);
        z->im = (b*c - a*d)/(c*c + d*d);
        printf("f = %g\t Z = %g + i*%g\n", f, z->re, z->im);
    }
}

void kont4 (complex *z,float R1, float R2, float L, float C, float Fmin, float Fmax, float Step){
    double a, b, c, d, f, f0, w;
    f0 = 1.0 / (2.0 * Pi * sqrt(L * C));
    printf("f0 = %g\n", f0);
    a = R1 * R2 + L/C;
    c = R1 + R2;
    for (f = Fmin; f < Fmax; f = f + Step){
        w = 2* Pi * f;
        b = w*L*R1 - R2/(w*C);
        d = w*L - (1/(w*C));
        z->re = (a*c + b*d)/(c*c + d*d);
        z->im = (b*c - a*d)/(c*c + d*d);
        printf("f = %g\t Z = %g + i * %g\n", f, z->re, z->im);
    }
    if(round(f * max_r) >= round(Fmax * max_r)){
        f = Fmax;
        w = 2* Pi * f;
        b = w*L*R1 - R2/(w*C);
        d = w*L - (1/(w*C));
        z->re = (a*c + b*d)/(c*c + d*d);
        z->im = (b*c - a*d)/(c*c + d*d);
        printf("f = %g\t Z = %g + i * %g\n", f, z->re, z->im);
    }
}
