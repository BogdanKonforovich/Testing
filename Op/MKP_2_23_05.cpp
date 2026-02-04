#include <iostream>
#include <cmath>
#include <windows.h>
using namespace std;

double add(double &a, double &b);
double add(double &a, double &b) {
    double d;
    d = pow(a, b);
    return d;
}
int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    double a, b;
    cout<<"Введіть будь-яке число та степінь, в який його треба піднести"<<endl;
    cin>>a>>b;
    cout<<"Результат: "<<add(a, b)<<endl;
    system("pause");
    return 0;
}
