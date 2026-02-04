#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <stdlib.h>

#define R 6
#define S 7

void ob_1(float mas[][S],int r, float midl);
// void ob_2(float mas[][S],int r, float midl);
int main() {

    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    float mas[R][S];
    float midl = R/2;
    ob_1(mas, R, midl);
    // ob_2(mas, R, midl);
    for(int i = 0; i < R; i++){
        for(int j = 0; j < S; j++){
            printf("%g  ", mas[i][j]);
        }
        printf("\n");
    }

    system("pause");
    return 0;
}
void ob_1(float mas[][S],int r, float midl){
    int i, j;
    float val = 0.5, m = 0.5;
    for(i = midl - 1; i >= 0; i--){
        if (i % 2 == 0){
            for(j = S-1; j >= 0; j--){
                mas[i][j] = m;
                m = m + val;
            }
        }else{
            for(j = 0; j < S; j++){
                mas[i][j] = m;
                m = m + val;
            }
        }
    }
    m = 0.5;
        for(i = midl; i < R; i++){
        if (i % 2 == 0){
            for(j = 0; j < S; j++){
                mas[i][j] = m;
                m = m + val;
            }
        }else{
            for(j = S-1; j >= 0; j--){
                mas[i][j] = m;
                m = m + val;
            }
        }
    }
}
// void ob_2(float mas[][S],int r, float midl){
//     int i, j;
//     float val = 0.5, m = 0.5;
//     for(i = midl; i < R; i++){
//         if (i % 2 == 0){
//             for(j = 0; j < S; j++){
//                 mas[i][j] = m;
//                 m = m + val;
//             }
//         }else{
//             for(j = S-1; j >= 0; j--){
//                 mas[i][j] = m;
//                 m = m + val;
//             }
//         }
//     }
// }

