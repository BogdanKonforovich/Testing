/*Дано масив розміром 4x6 з елементами цілого типу. Написати
програму для обчислення суми елементів масиву.*/
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <windows.h>
using namespace std;
int main()
{
SetConsoleCP(1251);
SetConsoleOutputCP(1251);
srand(time(NULL));
const int N = 4, M = 6;
int mas[N][M], sum = 0, n, m;
for (n = 0; n < N; n++){
    for (m = 0; m < M; m++){
        mas[n][m] = rand()%100;
        cout<<mas[n][m]<<"\t";
        sum = sum + mas[n][m];
    }
    cout<<endl;
}
cout<<"Сума всіх елементів масиву дорівнює "<<sum;
system("pause");
    return 0;
}
