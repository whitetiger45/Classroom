#include <iostream>
#include <string>

#define multiply( f1, f2 ) ( f1 * f2 )
#define store(a1, a2) (a1 = a2)
#define ask(typ, a) void add##typ() { std::cout<< a;}
ask(Num, "\nEnter a number: ")
ask(Word, "\nEnter a word: ")
ask(AnotherWord, "\nEnter next word: ")
ask(Phrase,"\nDo you want to make a phrase? 1 or 0: ")
ask(More, "More to add? 1 or 0: ")
#undef ask
#define func(n,a) void me##n() { std::cout << a;} 
func(nu, "Enter a value corresponding to the options below:\n1: Number\n2: Word\nUser: ")
#undef func
enum {number = 1, word};

using namespace std;

int main() 
{

    int z, y, q, userChoice = 0;
    std::string userWord, createdWord;
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
                    bool appendString = true;
                    int checkForMore = 0;
                    std::string nextWord;
                    addWord();
                    std::cin >> userWord;
                    addPhrase();

                    do
                    {
                        std::cin >> checkForMore;
                        appendString = checkForMore;
                        addAnotherWord();
                        std::cin >> nextWord;
                        userWord += " " + nextWord;
                        addMore();
                        std::cin >> checkForMore;
                        appendString = checkForMore;

                    }while(appendString);
                    std::cout << userWord << "\n";

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