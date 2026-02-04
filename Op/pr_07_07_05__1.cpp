// 3) Дано чотирьохзначне число. Вивести на екран в зворотньому
// порядку цифри, з яких складається число.
#include <iostream> 
#include <windows.h>
using namespace std;
int add(int a, int b);
int add(int a, int b){
    int x1, x2, x3, x4;
    
    x1 = a/1000;
    x2 = (a/100)%10;
    x3 = (a/10)%10;
    x4 = a%10; 
    b = x1 + (x2)*10 + (x3)*100 + x4*1000; 
    return b;
}
int main() {
SetConsoleCP(1251);
SetConsoleOutputCP(1251);
int numb, ob;
cout<<"Введіть будь-яке натуральне чотирьохзначне число "<<endl;
cin>>numb;
if (numb < 0){
    cout<<"Ви ввели не натуральне чотирьохзначне число!"<<endl;
    cout<<"Спробуйте ще раз!";
    system ("pause");
    return 0;  
}
if (numb<1000 || numb>9999){
    cout<<"Ви ввели не чотирьохзначне число!"<<endl;
    cout<<"Спробуйте ще раз!";
    system ("pause");
    return 0;  
}
ob = add (numb, ob);
cout<<"Обернене чотирьохзначне число: "<<ob<<endl;
system ("pause");
return 0;
}