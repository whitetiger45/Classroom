#include <cstdio>
#include <iostream>
#include <iterator>
#include <map>
#include <string>

using namespace std;

template<typename T>
T print(T i)
{
    cout<< i << "\n";
};

// http://stackoverflow.com/questions/23043936/using-template-iterator-in-c-stdmap

template<typename K, typename V>
// using kwargs = typename std::map<K,V>::const_iterator;//commented out to test setting of map value
using kwargs = typename std::map<K,V>::iterator;

template<typename K, typename V>
// std::map<K,V>& print(const std::map<K,V>& m) {//commented out to test setting of map value
std::map<K,V>& print(std::map<K,V>& m) {
    for (kwargs<K, V> iter = m.begin(); iter != m.end(); iter++) {
        std::cout << "Key: " << iter->first << " "
              << "Values: " << iter->second << std::endl;
        if (iter->first == 0)
        {
            iter->second = 7.2;
            std::cout << "Updayed Key: " << iter->first << " "
            << "New Values: " << iter->second << std::endl;
        }
    }
}

template<>
map<int,double>::iterator print<map<int,double>::iterator>(map<int,double>::iterator i)
{
    i++;int k2 = i->first;i--;int dupCount = 0;
    while(dupCount != 1){
        if(i->first == k2)
            dupCount++;
        std::cout << i->first << " => " << i->second << "\n";
        std::advance(i,1);
    }
}

template<>
double print<double>(double i)
{
    cout<< i << "\n";
}

template<>
string print<string>(string i)
{
    cout<< i << "\n";
}

template<>
int print<int>(int i)
{
    cout<< i << "\n";
}

int print (int i)
{
    cout<< i << "\n";
}


/*
this also works
template<typename ...Args>
void pass(Args... args)
{
}

template<typename ...args>
void f(args... a)
{
    pass( print(a)... ); //this works
}
http://stackoverflow.com/questions/5481539/what-does-t-double-ampersand-mean-in-c11
*/
 
 //http://e...content-available-to-author-only...e.com/w/cpp/language/parameter_pack
template<typename T, typename... Targs>
void f2(T a, Targs... Fargs) 
{
    print(a, Fargs...);
}

template<typename ...Args>
void pass(Args&&... args)
{
}

template<typename ...args>
void f(args&&... a)
{
    // print(a) ...; //this doesn't expand
    pass( print(a)... ); //this works

}

int main() 
{
    map <int,double> x;
    x[0] = 2.7;
    x[1] = 4.5;
    map <int,double>::iterator xi = x.begin();

    // f(2, 1.1,"hello",xi); // OK: args contains two arguments: int and double
    // f2(2, 1.1,"hello"); // OK: args contains two arguments: int and double
    // f("hello", "world", 9,18, "goodbye");
    f("hello", "world", x, 7, 45, "bye!");
    // f2(1);
    return 0;
}