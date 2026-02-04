#include <iostream>
using namespace std;
int main()
{
    const int n = 9, m = 9;
    int mas[n][m], i, j, k = 0, c = 1;
    while (k < (n + 1) / 2){
        for (j = 0 + k; j < m - k; j++, c++) {
            i = 0 + k;
            mas[i][j] = c;  
            }
        for (i = 1 + k; i < n - k; i++, c++){
            j = 8 - k;
            mas[i][j] = c; 
        }
        for (j = 7 - k; j >= k; j--, c++){
            i = 8 - k;
            mas[i][j] = c;
        }
        for (i = 7 - k; i > k; i--, c++){
            j = 0 + k;
            mas[i][j] = c;
        }
        k++;
    }
    for (i = 0; i < n; i++){
        for (j = 0; j < m; j++){
            cout<<mas[i][j]<<"\t";  
            }
            cout<<endl;
    }
system("pause");
    return 0;
}