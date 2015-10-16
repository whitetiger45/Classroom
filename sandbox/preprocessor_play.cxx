#include <iostream>
#include <string>

#define multiply( f1, f2 ) ( f1 * f2 )
#define store(a1, a2) (a1 = a2)
#define ask(typ, a) void add##typ() { std::cout<< a;}
ask(Num, "Enter a number: ")
ask(Word, "Enter a string: ")
ask(More, "More to add? 1 or 0: ")
#undef ask
using namespace std;

int main() 
{
    int z, y, q;
    std::string p, v;
    std::string a;
    bool more = true;
    do{
        addNum();
        std::cin >> z;
        addNum();
        std::cin >> y;

        addWord();
        std::cin >> p;
        auto x = multiply(z, y);
        store(v, p);
        std::cout << z << " * " << y << ": " << x << "\n";
        std::cout << v << "\n";

        //addWord();
        /*give("apple");
        std::cout << give << "\n";
        //give(p);*/
        addMore();
        std::cin >> q;
        more = q;

    }while(more);
    return 0;
}