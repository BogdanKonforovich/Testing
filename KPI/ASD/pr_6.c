#include <stdio.h>
#include <math.h>
#include <windows.h> 
#define r 6
#define s 7

void stov (int sp[][s], int pot[], int rd, int sb);
void conclusion (int m[][s],int rd);
void bubbleSortRows (int mas[][s], int rd);

int main() {

    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    
    int i, j, mas[r][s] = {
        {12, 45, 78, 23, 56, 89, 34},
        {67, 2, 90, 11, 38, 47, 53},
        {81, 14, 29, 66, 5, 72, 19},
        {44, 91, 3, 57, 88, 21, 39},
        {7, 63, 50, 26, 95, 18, 32},
        {60, 13, 84, 41, 9, 77, 28} },
    sum[s] = {0};

    printf("Початковий масив:\n");
    conclusion(mas, r);

    stov (mas, sum, r, s);

    bubbleSortRows (mas, r);

    printf("Відсортований масив:\n");
    conclusion(mas, r);
    system("pause");
    return 0;
}

void stov (int sp[][s], int pot[], int rd, int sb){
    int i, j;
    for (j = 0; j < sb; j++){
        for(i = 0; i < rd; i++){
            pot[j] = pot[j] + sp[i][j];
        }
        printf("Сума %d стовпчика: %d \n", j+1, pot[j]);
    }
}

void bubbleSortRows (int mas[][s], int rd){
    int k, i, j, temp;
    for(k = 0; k < rd; k++){
        for (i = 0; i < s - 1; i++){
            for (j = 0; j < s - i - 1; j++){
                if(mas[k][j] > mas[k][j+1]){
                    temp = mas[k][j];
                    mas[k][j] = mas[k][j+1];
                    mas[k][j+1] = temp;
                }
            }
        }
    }
}

void conclusion (int m[][s],int rd){
    int i, j;
    for(i = 0; i < rd; i++){
    for (j = 0; j < s; j++){
        printf("%d ", m[i][j]);
    }
    printf("\n");
    }
}