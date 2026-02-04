#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <windows.h>

#define min_x 1E-2
#define max_x 720
#define min_dx 1E-2
#define O 0
#define min_E 1
#define max_E 6
#define Pi 3.141592653589793
#define iter 50
#define step 1000
#define EPS 1e-9


float Per1 (float x, char name[], float max, float min){
    char en, m;
    do {
        m = 0;
        if(scanf("%f%c", &x, &en) != 2 || en != '\n'){
            printf("Введіть значення в правильній формі (Наприклад 21.5) \nПовторіть спробу:");
            while (getchar() != '\n');
            m = 1;
        } else {
            if (fabs(x) < min - EPS && x != O || fabs(x) > max ){
                printf ("%s задано в неправильному діапазоні \nПовторіть спробу:", name);
                m = 1;
            }
        }
    } while (m);
    return x;
}

int main() {

    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    
    int E, n, j, steps;
    char x1n[] = "x1", x2n[] = "x2", dxn[] = "dx", xn = 'x', En = 'E', m, en, prod;
    float x1, x2, xr, dx, x;
    double toch, delta, sinx, riz;
    
    do{
        m = 0;
        printf ("Введіть значення %s (|%s| повинен бути в межах від %g до %d (%d також підходить)) \n", x1n, x1n, min_x, max_x, O);
        x1 = Per1 (x1, x1n, max_x, min_x);
        printf ("Введіть значення %s (|%s| повинен бути в межах від %g до %d (%d також підходить)) \n", x2n, x2n, min_x, max_x, O);
        x2 = Per1 (x2, x2n, max_x, min_x);
        printf ("Введіть %s (крок зміни) (|%s| повинен бути в межах від %g до %d) \n", dxn, dxn, min_dx, max_x);
        dx = Per1 (dx, dxn, max_x, min_dx);
        
        steps = ((x2 - x1)/dx);
        if (steps > step) {
            printf("Занадто багато кроків (%d) (Максимум %d) . Збільшіть dx або зменшіть x2.\n", steps, step);
            m = 1;
        }else{
            if(x1 != x2 && dx == 0){
                printf ("Введені значення не відповідають вимогам для кроку (Якщо %s не дорівнює %s, тоді %s не повинен дорівнювати %d ) \n", x1n, x2n, dxn, O);
                m = 1;
            }
            if(x1 < x2 && dx <= 0){
                printf ("Введені значення не відповідають вимогам для кроку (Якщо %s < %s, тоді %s > %d ) \n", x1n, x2n, dxn, O);
                m = 1;
            }
            if(x1 > x2 && dx >= 0){
                printf ("Введені значення не відповідають вимогам для кроку (Якщо %s > %s, тоді %s < %d ) \n", x1n, x2n, dxn, O);
                m = 1;
            }
        }
        if(m == O){
            printf("Введіть значення %c (точність обчислень) (%c повинно від %d до %d):\n",En, En, min_E , max_E);
            do {
                m=0;
                if(scanf ("%d%c", &E, &en) != 2 || en!='\n')
                {
                    printf ("Введіть %c в правильній формі!(Тільки цілі числа)\nПовторіть спробу введення %c\n", En, En);
                    m=1;
                    while (getchar() != '\n');
                } 
                else {
                    if (E < min_E || E > max_E) {
                        printf ("%c задано в неправильному діапазоні\nПовторіть спробу введення %c\n", En, En);
                        m = 1;
                    }
                }
            } 
            while (m);
            toch = 1;
            for(int i = 0; i < E; i++){
                toch = 0.1 * toch;
            }
            x = x1;

            if (x1 < x2){
                j = 0;
                do{
                    if (j == iter){
                        printf("Якщо бажаєте продовжити обчислення натисніть 1, інакше 2!");
                        prod = getchar();
                        while (getchar() != '\n'); //getchar() читає символ нового рядка \n, який залишився у буфері
                        j = 0;
                        if(prod != '1'){
                            break;
                        }
                    }
                    xr = (x*Pi)/180.;
                    while (xr > 2 * Pi)
                        xr = xr - 2 * Pi;
                    while (xr < -2 * Pi)
                        xr = xr + 2 * Pi;
                    delta = sinx = xr;
                    n = 1;
                    do{
                        delta = delta*((-xr*xr)/((n+1)*(n+2)));
                        sinx = sinx + delta;
                        n = n + 2;
                    } while (fabs(delta)>toch);
                    riz = sin(xr) - sinx;
                    // if (((int)x % 180) == 0) {
                    //     sinx = 0.0;
                    //     riz = 0.0;
                    // }
                    printf("%c = %g\t sin(x) = %.*lf\t found sin(x) = %.*lf\t difference = %g\n", xn, x, E, sin(xr), E, sinx, riz);
                    j++;
                    x = x + dx;
                    x = round(x * 1e2) / 1e2;
                }while (x < x2);
                if(x >= x2){
                    x = x2;
                    xr = (x*Pi)/180.;
                    while (xr > 2 * Pi)
                        xr = xr - 2 * Pi;
                    while (xr < -2 * Pi)
                        xr = xr + 2 * Pi;
                    delta = sinx = xr;
                    n = 1;
                    do{
                        delta = delta*((-xr*xr)/((n+1)*(n+2)));
                        sinx = sinx + delta;
                        n = n + 2;
                    } while (fabs(delta)>toch);
                    riz = sin(xr) - sinx;
                    // if (((int)x % 180) == 0) {
                    //     sinx = 0.0;
                    //     riz = 0.0;
                    // }
                    printf("%c = %g\t sin(x) = %.*lf\t found sin(x) = %.*lf\t difference = %g\n", xn, x, E, sin(xr), E, sinx, riz);
                }
            }
            if (x1 > x2){
                j = 0;
                do{
                    if (j == iter){
                        printf("Якщо бажаєте продовжити обчислення натисніть 1, інакше 2!");
                        prod = getchar();
                        while (getchar() != '\n');
                        j = 0;
                        if(prod != '1'){
                            break;
                        }
                    }
                    
                    xr = (x*Pi)/180.;
                    while (xr > 2 * Pi)
                        xr = xr - 2 * Pi;
                    while (xr < -2 * Pi)
                        xr = xr + 2 * Pi;
                    delta = sinx = xr;
                    n = 1;
                    do{
                        delta = delta*((-xr*xr)/((n+1)*(n+2)));
                        sinx = sinx + delta;
                        n = n + 2;
                    } while (fabs(delta)>toch);
                    riz = sin(xr) - sinx;
                    // if (((int)x % 180) == 0) {
                    //     sinx = 0.0;
                    //     riz = 0.0;
                    // }
                    printf("%c = %g\t sin(x) = %.*lf\t found sin(x) = %*lf\t difference = %g\n", xn, x, E, sin(xr), E, sinx, riz);
                    j++;
                    x = x + dx;
                    x = round(x * 1e2) / 1e2;
                }while (x > x2);
                if(x <= x2){
                    x = x2;
                    xr = (x*Pi)/180.;
                    while (xr > 2 * Pi)
                        xr = xr - 2 * Pi;
                    while (xr < -2 * Pi)
                        xr = xr + 2 * Pi;
                    delta = sinx = xr;
                    n = 1;
                    do{
                        delta = delta*((-xr*xr)/((n+1)*(n+2)));
                        sinx = sinx + delta;
                        n = n + 2;
                    } while (fabs(delta)>toch);
                    riz = sin(xr) - sinx;
                    // if (((int)x % 180) == 0) {
                    //     sinx = 0.0;
                    //     riz = 0.0;
                    // }
                    printf("%c = %g\t sin(x) = %.*lf\t found sin(x) = %*lf\t difference = %g\n", xn, x, E, sin(xr), E, sinx, riz);
                }
            }
            if (x1==x2){
                xr = (x*Pi)/180.;
                while (xr > 2 * Pi)
                    xr = xr - 2 * Pi;
                while (xr < -2 * Pi)
                    xr = xr + 2 * Pi;
                delta = sinx = xr;
                n = 1;
                do{
                    delta = delta*((-xr*xr)/((n+1)*(n+2)));
                    sinx = sinx + delta;
                    n = n + 2;
                } while (fabs(delta)>toch);
                riz = sin(xr) - sinx;
                    // if (((int)x % 180) == 0) {
                    //     sinx = 0.0;
                    //     riz = 0.0;
                    // }
                printf("%c = %g\t sin(x) = %.*lf\t found sin(x) = %.*lf\t difference = %g\n", xn, x, E, sin(xr), E, sinx, E, riz);
            }
        }

        printf ("Щоб закінчити програму, натисніть ESC!\n" "Якщо хочете ще раз скористатися, натисніть Enter\n");
    }   while (getch()!=27);
    return 0; 
}