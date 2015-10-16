#include <iostream>
#include <string>

#define multiply( f1, f2 ) ( f1 * f2 )
#define store(a1, a2) (a1 = a2)
#define ask(typ, a) void add##typ() { std::cout<< a;}
ask(Num, "\nEnter a number: ")
ask(Word, "\nEnter a word: ")
ask(AnotherWord, "\nEnter next word: ")
ask(Phrase,"\nDo you want to make a phrase? [y or n]: ")
ask(NextString, "\nExtend phrase? [y or n]: ")
ask(More, "Restart program? [y or n]: ")
#undef ask
#define func(n,a) void me##n() { std::cout << a;} 
func(nu, "Enter a value corresponding to the options below:\n1: Number\n2: Word\nUser: ")
#undef func
enum {number = 1, word};
enum {n , y};
char option[] = {'n', 'y'};


using namespace std;

int main() 
{

    int z, y, userChoice = 0;
    char userWantsToContinue;
    std::string userWord, createdWord;//created word is currently unused
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
                    char checkForMore ;
                    int count = 0;
                    std::string nextWord;
                    addWord();
                    std::cin >> userWord;
                    while(appendString)
                    {
                        if(count == 0)
                        {
                            addPhrase();
                            std::cin >> checkForMore;
                            appendString = (checkForMore == option[n]) ? false : true;
                            count++;
                        }
                        else
                        {
                            addNextString();                            
                            std::cin >> checkForMore;
                            appendString = (checkForMore == option[n]) ? false : true;
                        }
                        if(!appendString)
                            break;
                        addAnotherWord();
                        std::cin >> nextWord;
                        userWord += " " + nextWord;
                    }
                    std::cout << userWord << "\n";

                    break;
            }
            default:
                    std::cout << "\nYou did not enter a valid option!\n";
        }

        addMore();
        std::cin >> userWantsToContinue;
        more = (userWantsToContinue == option[n]) ? false : true;

    }while(more);
    return 0;
}