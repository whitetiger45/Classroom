#include <iostream>
#include <cstdio>
#include <string>
#include <map>
#include <iterator>
#include <set>

using namespace std;

template<typename T>
T print(T i)
{
    cout<< i << "\n";
};

template<>
map<int,double>::iterator print<map<int,double>::iterator>(map<int,double>::iterator i)
{
    i++; int k2 = i->first; i--;int dupCount = 0;
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
the below templates (pass, f), were started by someone else who I can't find the stackover-flow 
message board I got the original code from. 

*/

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

    f(2, 1.1,"hello",xi,'h','i'); // OK: args contains two arguments: int and double
    // f(2, 1.1,"hello"); // OK: args contains two arguments: int and double
    f("hello", "world", 9,18, "goodbye");
    return 0;
}