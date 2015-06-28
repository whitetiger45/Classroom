// Recursive power function generated from algorithm described in 'Data Structures and Algorithms in C++'
//Michael T. Goodrich * Roberto Tamassia * David Mount
//Page 176
#include <iostream>
using namespace std;
 
int power(int x, int p)
{
    if(p == 0)
        return 1;
    else if(p % 2 == 1)
        return (x * (power(x, (p-1)/2) * (power(x, (p-1)/2))));
    else 
        return (power(x, p/2) * power(x, p/2));
}
 
int main() 
{
    int x = 3;
 
    cout << "Power: 3 ^ 4: " << power(x, 4) << "\n";
 
    return 0;
}