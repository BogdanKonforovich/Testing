// Використовуючи підпрограми протабулювати функцію, яку задає користувач на проміжку, 
// який задає користувач та визначити, для якого х функція набуває мінімального значення.
#include <iostream> 
#include <windows.h>
#include <iomanip>
using namespace std;
double add (int a, int b);

double add (int a, int b){
    int x, x_min = 0;
    double y;
    double min_y;
    cout<<"-----------------"<<endl;
    cout<<"|"<<"y"<<"\t"<<"|"<<"x"<<"\t"<<"|"<<endl;
    cout<<"-----------------"<<endl;
    for(x = a; x <= b; x++){
        y = (x*2+3)/3.0;
        cout.precision(3);
        cout<<"|"<<y<<"\t"<<"|"<<x<<"\t"<<"|"<<endl;
        cout<<"-----------------"<<endl;
    }
    min_y = y;
    for (x = b - 1; x >= a; x--){
        y = (x*2+3)/3.0;
        if (min_y > y){
            min_y = y;
            x_min = x;
        }
    }
    cout<<"Мінімальне значення y дорівнює "<<min_y<<", коли x дорівнює "<<x_min<<endl;
    return 0;
}

int main() {
SetConsoleCP(1251);
SetConsoleOutputCP(1251);
int a, b;
cout<<"Функція має вигляд: y = (x*2+3)/3"<<endl;
cout<<"Введіть інтервал значень x"<<endl;
cout<<"Початкове значення х : ";
cin>>a;
cout<<"Кінцеве значення х : ";
cin>>b;
if (a > b){
    cout<<"Початкове значення не може бути більшим кінцевого"<<endl;
    system ("pause");
    return 0;
}
add (a, b);
system ("pause");
return 0;
}