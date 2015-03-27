#include <iostream>
#include <string>

using namespace std;

template<class ... T>
class VariadicTemplate;

template<>
class VariadicTemplate<int, string>
{
public:

    VariadicTemplate();
    VariadicTemplate(int x, string str)
    {
        number = x;
        word = str;
    };
    void print()
    {
        cout<<"About to print your Variadic Template variables...\n";
        cout << "Word: "<< word << ", Number: "<< number << "\n";
    }

    void setWord(string str)
    {
        word = str;
    }

    void setNumber(int x)
    {
        number = x;
    }

private:
    string word;
    int number;

};

int main()
{
    VariadicTemplate<int, string> vtExample(9, std::string("twenty-three"));
    vtExample.print();
}