#include <iostream>
using namespace std;

int main() 
{
    int row, c = 1, blk, i, j; 


    cout << "\nMembuat Segita Pascal siku-siku\n"; //\n memberikan spasi untuk input 
    cout << "Masukkan Pola: ";

    cin >> row; 

    for (i = 0; i < row; i++) 
    {
       for (j = 0; j <= i; j++)  
    {
        if (j == 0 || i == 0)
        c = 1;
        else
        c = c * (i - j + 1) / j;
        cout << c << " ";
    }
    cout << endl;
    }

}
