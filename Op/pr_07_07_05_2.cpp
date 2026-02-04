// 1) Організувати безперервне введення чисел з клавіатури, поки
// користувач не вводить 0. після вводу 0, вивести на екран кількість чисел, їх
// загальну суму, середнє арифметичне.
#include <iostream> 
#include <windows.h>
using namespace std;
void add(int &a, int &b, double &c);
void add(int &a, int &b, double &c){
    int d;
    a = b = c = 0;
    cout<<"Введіть будь-які числа, закінчивши введення нулем (0)"<<endl;
    while(true){
        cin>>d;
        if (d == 0){
            c = (double)a/b;
            break;
        }
        a = a + d;
        b++;
    }
}
int main() {
SetConsoleCP(65001);
SetConsoleOutputCP(65001);
int sum, kil;
double arf;
add (sum, kil, arf);
cout<<"Сума всіх введених елементів: "<<sum<<endl;
cout<<"Кількість всіх введених елементів: "<<kil<<endl;
cout<<"Середнє арифметичне введених елементів: "<<arf<<endl;
system ("pause");
return 0;
}