#include <iostream>
#include <string>

#define multiply( f1, f2 ) ( f1 * f2 )
#define store(a1, a2) (a1 = a2)
#define a(name) std::string (a = name)
using namespace std;

//this program was created using ideone, so the input values are usually given as input on the webpage

int main() 
{
    int z, y;
    std::string p, v;
    std::cin >> z >> y >> p;
    auto x = multiply(z, y);
    store(v, p);
    std::cout << z << " * " << y << ": " << x << "\n";
    std::cout << v << "\n";
    std::string a;
    a("apple");
    std::cout << a << "\n";
    return 0;
}