//Визначити максимальні елементи в усіх рядках.//
#include <iostream>
#include <Windows.h> 
#include <ctime>
#include <cstdlib>
using namespace std;
int main()
{
SetConsoleCP(1251);
SetConsoleOutputCP(1251);
srand(time(NULL));
const int N = 5, M = 5, R = 5, Nom = 5;
int n, m, r = 0, sum = 0;
int max[R], mas[N][M], ind[Nom];
for (n = 0; n < N; n++){
    for (m = 0; m < M; m++){
        mas[n][m] = rand()%200 - 100;
        cout<<mas[n][m]<<"\t";
    }
    cout<<endl;
} 
for (r = 0; r < R; r++){
    max[r] = -101;
}
for (n = 0; n < N; n++){
    for (m = 0; m < M; m++){
        if (max[n] < mas[n][m]){
            max[n] = mas[n][m];
            ind[n] = m + 1;
        }
    }
}
for (n = 0; n < N; n++){
    cout<<"Максимальний елемент "<<n + 1<<" рядка під номером "<<ind[n]<<" і дорівнює "<<max[n];
    cout<<endl;
}
system("pause");
    return 0;
}