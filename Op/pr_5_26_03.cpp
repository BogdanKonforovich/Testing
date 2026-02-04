/*Криптографія. Придумати та описати словесно власний спосіб
шифрування тексту. Скласти програму для введення тексту як даного типу
string (до 255 символів), його шифрування і виведення результату.*/
#include <iostream>
#include <Windows.h>
#include <string.h>
using namespace std;
int main (){
SetConsoleCP(1251);
SetConsoleOutputCP(1251);
cout<<"Перша частина"<<endl;
char n[255];
cout<<"Введіть текст для шифрування: "<<endl;
cin.getline(n, 255);
int i = strlen(n), k, m , j = i/2;
char n1;
for (k = i - 1, m = 0; k >= j && m <= j; k = k-2, m = m+2){
    n1 = n[k];
    n[k] = n[m];
    n[m] = n1; 
}
cout<<"Зашифрований текст: "<<n<<endl;
cout<<"Друга частина"<<endl;
char q[255];
cout<<"Введіть будь-який арифметичний вираз який містить дужки: "<<endl;
cin.getline(q, 255);
int w = strlen(q), vid = 0, zak = 0, t;
for (t = 0; t < w; t++){
    if (q[t] == '('){
        vid++;
    }
    if (q[t] == ')'){
        zak++;
    }
}
if (vid == zak && vid != 0 && zak != 0){
    cout<<"Дужки введено правильно"<<endl;
}
else if (vid > zak){
    cout<<"Кількість відкритих дужок більже ніж закритих"<<endl;
}
else if (vid < zak){
    cout<<"Кількість закритих дужок більше ніж відкритих"<<endl;
}
else{
    cout<<"У виразі відсутні дужки!"<<endl;
}
system("pause");
return 0;
}