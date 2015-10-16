#include <iostream>
#include <string>

#define multiply( f1, f2 ) ( f1 * f2 )
#define store(a1, a2) (a1 = a2)
#define ask(typ, a) void add##typ() { std::cout<< a;}
ask(Num, "\nEnter a number: ")
ask(Word, "\nEnter a string: ")
ask(More, "More to add? 1 or 0: ")
#undef ask
#define func(n,a) void me##n() { std::cout << a;} 
func(nu, "Enter a value corresponding to the options below:\n1: Number\n2: Word\nUser: ")
#undef func
#define number 1
#define word 2

using namespace std;

int main() 
{

    int z, y, q, userChoice = 0;
    std::string p, v;
    std::string a;
    bool more = true;
    do{
        menu();
        std::cin >> userChoice;
        switch(userChoice)
        {
            case number:
            {
                addNum();
                std::cin >> z;
                addNum();
                std::cin >> y;
                auto x = multiply(z, y);
                std::cout << z << " * " << y << ": " << x << "\n";

                break;
            }
            case word:
            {
                    addWord();
                    std::cin >> p;
                    store(v, p);
                    std::cout << v << "\n";

                    break;
            }
            default:
                    std::cout << "\nYou did not enter a valid option!\n";
        }
        addMore();
        std::cin >> q;
        more = q;

    }while(more);
    return 0;
}