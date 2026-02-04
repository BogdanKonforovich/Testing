/*Ввести прізвище, ім’я та побатькові як одне дане типу рядок.
Визначити довжину рядка і кількість букв “а” у ньому. Вивести
найдовше слово.*/
#include <iostream>
#include <Windows.h>
#include <string.h>
using namespace std;
int main (){
SetConsoleCP(1251);
SetConsoleOutputCP(1251);
char name[150];
cout<<"Введіть ім'я, прізвище та ім'я по батькові: ";
cin.getline(name, 150);
int n, i = strlen(name), k = 0;

for(n = 0; n < i ; n++){
    if (name[n] == ' '){
        i--;
    }
    if(name[n] == 'а' || name[n] == 'А' || name[n] == 'a' || name[n] == 'A'){
        k++;
    }
}
cout<<"Довжиння ПІБ: "<<i<<endl;
cout<<"Кількість літер а: "<<k<<endl;
int mas[3] = {0}, j = 0;
k = 1;
for(n = 0; n < i; n++, k++){
    mas[j] = k;
    if(name[n] == ' '){
        mas[j] = mas[j] - 1;
        j++;
        k = 0;
    }
}
if(mas[0] > mas [1] && mas[0] > mas[2]){
    cout<<"Найбільше букв в прізвищі: "<<mas[0]<<endl;
}
else if(mas[1] > mas [0] && mas[1] > mas[2]){
    cout<<"Найбільше букв у імені: "<<mas[1]<<endl;
}
else if(mas[2] > mas [0] && mas[2] > mas[1]){
    cout<<"Найбільше букв в імені по батькові: "<<mas[2]<<endl;
}
else{
    cout<<"Кількість букв однакові: "<<mas[1]<<endl;
}
system("pause");
return 0;
}