// Написати програму, яка за введеними сторонами трикутника
// обчислює: Площу; Периметр; Висоти; Бісектриси; Медіани.
#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <windows.h>

float area(float x, float y, float z){ // Знаходження площі
    float area, p;
    p = (x + y + z)/2;
    area = sqrt(p*(p-x)*(p-y)*(p-z)); 
    return area;
}
float Per(float x, float y, float z){ // Знаходження периметру
    float  p;
    p = x + y + z;
    return p;
}
float height(float x, float y, float z){ //Знаходження висоти до сторони x
    float height_x, p;
    p = (x + y + z)/2;
    height_x = (2*sqrt(p*(p-x)*(p-y)*(p-z)))/x; 
    return height_x;
}
float Med(float x, float y, float z){ // Знаходження медіани до сторони x
    float Med_x;
    Med_x = (sqrt(2*pow(y, 2)+2*pow(z, 2)-pow(x, 2)))/2; 
    return Med_x;
}
float Bis(float x, float y, float z){ // Знаходження бісектриси до сторони x
    float Bis_x, p;
    p = (x + y + z)/2;
    Bis_x = (2 * sqrt(y * z * p * (p - x))) / (y + z);
    return Bis_x;
}
float Per1(float x, char d, char name){ // Чи сторона більше 0
    if (x<=0){
        printf ("Сторона %c повинна бути більше 0\n", name);
        return 1;
    }
    return 0;
}
float Per2(float x, char d, char name){ // Чи сторона має допустиме значення
    if (x < 0.000001 || x > 100000){
        printf("Сторона %c повинна бути в межах від 0.00001 до 10000\n", name);
        return 1;
    }
    return 0;
}
float Per3(float x, float y, float z, char d, char name){ // Чи сторона менше суми двох інших сторін
    if (y+z<=x){
        printf ("Сторона %c не може бути більшою або дорівнювати сумі інших двох сторін!\n", name);
        return 1;
        }
    return 0;
}

int main() {

    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    
    float a, b, c, S, P, Ha, Hb, Hc, Ma, Mb, Mc, Ba, Bb, Bc;
    char d, m, ch, a_n = 'a', b_n = 'b', c_n = 'c';
    do {
        do {        // Перевірка чи більші 0 ст. трикутника
            d = 0;
            printf ("Введіть сторони трикутника: a, b, c (сторони повинні бути в межах від 0.00001 до 10000)\n");
            if(scanf ("%f %f %f%c", &a, &b, &c, &ch) != 4 || ch!='\n')
            {
                printf ("Введіть числа у правильній формі!(Приклад: 1.43)\n");
                d=1;
                while (getchar() != '\n'); // чистимо буфер
            }
            else{
                if (Per1(a, d, a_n) || Per1(b, d, b_n) || Per1(c, d, c_n)){
                    d=1;
                } else {
                    if (Per2(a, d, a_n) || Per2(b, d, b_n) || Per2(c, d, c_n)){
                        d=1;
                    } 
                    else {
                        if (Per3(a, b, c, d, a_n) || Per3(b, a, c, d, b_n) || Per3(c, b, a, d, c_n)){
                            d=1;
                        }   
                    }
                }
            }
        }    
        while (d);

        S = area(a, b, c);
        printf ("Площа трикутника дорівнює: %f\n", S);

        P = Per(a, b, c);
        printf ("Периметр трикутника дорівнює: %f\n", P);

        Ha = height(a, b, c);
        printf ("Висота трикутника до сторони a дорівнює: %f\n", Ha);
        Hb = height(b, a, c);
        printf ("Висота трикутника до сторони b дорівнює: %f\n", Hb);
        Hc = height(c, b, a);
        printf ("Висота трикутника до сторони c дорівнює: %f\n", Hc);

        Ma = Med(a, b, c);
        printf ("Медіана трикутника до сторони a дорівнює: %f\n", Ma);
        Mb = Med(b, a, c);
        printf ("Медіана трикутника до сторони b дорівнює: %f\n", Mb);
        Mc = Med(c, b, a);
        printf ("Медіана трикутника до сторони c дорівнює: %f\n", Mc);

        Ba = Bis(a, b, c);
        printf ("Бісектриса трикутника до сторони a дорівнює: %f\n", Ba);
        Bb = Bis(b, a, c);
        printf ("Бісектриса трикутника до сторони b дорівнює: %f\n", Bb);
        Bc = Bis(c, b, a);
        printf ("Бісектриса трикутника до сторони c дорівнює: %f\n", Bc);

        printf ("Щоб закінчити програму, натисніть ESC!\n" "Якщо хочете продовжити, натисніть будь-яку клавішу (окрім ESC)\n");
    }
    while (getch()!=27);
    return 0; 
}
