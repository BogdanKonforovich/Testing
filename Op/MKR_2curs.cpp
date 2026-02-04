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
    int N, n, k = 0;
    cout<< "Введіть розмір масиву "<<endl;
    cin>>N;
    int mas[N];
    cout<<"Масив має вигляд "<<endl;
    for (n = 0; n < N; n++){
        mas[n] = rand()%200 - 100;
        if (mas[n] > 0){
            k++;
        }
        if (n % 5 == 0){
            cout<<endl;
        }
        cout<<mas[n]<<"\t";
    }
    cout<<endl;
    cout<<"Кількість додатних елементів масиву: "<<k<<endl;
    system("pause");
    return 0;
}