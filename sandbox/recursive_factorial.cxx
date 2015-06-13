#include <iostream>
#include <cstdint>
 
using namespace std;
 
uint64_t rF(uint64_t n)
{
    if (n == 0)
        return 1;
    else 
        return (n * rF(n-1));
}
 
int main() 
{
    uint64_t x = 0;
 
    x = rF(20);
    cout << "X: " <<  x << "\n";
 
    return 0;
}