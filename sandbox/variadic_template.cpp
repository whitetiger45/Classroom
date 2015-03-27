#include <algorithm>
#include <iostream>
#include <string>
#include <tuple>
#include <typeinfo>
#include <vector>

using namespace std;

// ----------------------------------------------------------------------

 template<int index, typename... Ts>
 struct print_tuple
 {
     void operator() (tuple<Ts...>& t) 
     {
         cout << get<index>(t) << " ";
         print_tuple<index - 1, Ts...>{}(t);
     }
 };

 template<typename... Ts>
 struct print_tuple<0, Ts...> 
 {
     void operator() (tuple<Ts...>& t) 
     {
         cout << get<0>(t) << " ";
     }
 };

 template<typename... Ts>
 void print(tuple<Ts...>& t) 
 {
     const auto size = tuple_size<tuple<Ts...>>::value;
     print_tuple<size - 1, Ts...>{}(t);
 }
// -----------------------------------------------------------------------
template<class ... T>
class VariadicTemplate;

template<class... T> 
void func(tuple<T&& ...> args )
{
    cout << sizeof...(T) << "\n";
    size_t size = sizeof...(T);
    
    cout << "Tuple args: " << get<0>(args) << ", " << get<1>(args) << "\n---------------------\n";

    print(args);

    cout << "\n";
}

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

    int getNumber(){return number;}

    string getWord(){return word;}

private:
    string word;
    int number;
    // tuple<int, string> vals;

};

template<>
class VariadicTemplate<string, string>
{
public:

    VariadicTemplate();
    VariadicTemplate(string x, string str)
    {
        number = x;
        word = str;

    };
    void print()
    {
        cout<<"About to print your Variadic Template variables...\n";
        cout << "Word: "<< word << ", Number: "<< number << "\n";
    }

    void setWord(string str, string x)
    {
        word = str;
        number = x;
    }
    string getNumber(){return number;}

    string getWord(){return word;}

private:
    string word;
    string number;
    // tuple<T, string> vals;

};


template<>
class VariadicTemplate<string, int, vector<int>>
{
public:

    VariadicTemplate();
    VariadicTemplate(string w, int val, vector<int> vec)
    {
        store = vec;
        word = w;
        value = val;
    };

    void print()
    {
        cout<<"About to print your Variadic Template variables...\n";
        cout << "Word: "<< word << ", Number: "<< value << ", Stored vector contains: ";

        for_each(store.begin(), store.end(), [&](int x){cout<< x * (value) << " ";});
        cout<< "\n";
    }
private:
    vector<int> store;
    string word;
    int value;

};

int main()
{
    VariadicTemplate<int, string> vtExample(9, std::string("twenty-three"));
    vtExample.print();

    func(forward_as_tuple(9, 23, vtExample.getWord(), vtExample.getNumber()));

    func(forward_as_tuple(string("nine"), 23, vtExample.getWord(), vtExample.getNumber()));
    auto t = make_tuple(1, 2, "abc", "def", 4.0f);
    vector<int> cc;
    for(int i = 0; i < 5; i++)
        cc.push_back(i);

    for(int v : cc)
        cout<< v << " ";

    cout << "\n";

    VariadicTemplate<string, int, vector<int>> vtExample2("wu wei", 3, cc);
    vtExample2.print();
    // auto tv = make_tuple(i.begin(), i.end())
    // func(forward_as_tuple(i));
    print(t);
}