#include <algorithm>
#include <bitset>
#include <ctime>
#include <iostream>
#include <iterator>
#include <list>
#include <string>

//original class taken from
//http://rosettacode.org/wiki/Sierpinski_triangle#C.2B.2B
 
using namespace std;
 
template<typename OutIt>
void sierpinskiDwn(int n, OutIt result)
{
    if( n == 0 )
    {
        *result++ = "*";
    }
    else
    {
        list<string> prev;
        sierpinskiDwn(n-1, back_inserter(prev));
        //cout <<  std::bitset<5>(1 << (n-1)) << "\n" ;
        string sp(1 << (n-1), ' ');
        result = transform(prev.begin(), prev.end(),
            result,
            [](const string& x) { return x + " " + x; });
            transform(prev.begin(), prev.end(),
            result,
            [sp](const string& x) { return sp + x + sp; });
    }
}

template<typename OutIt>
void sierpinskiHazardUp(int n, OutIt result)
{
    if( n == 0 )
    {
        *result++ = "*";
    }
    else
    {
        list<string> prev;
        sierpinskiDwn(n-1, front_inserter(prev));

        string sp(1 << (n-1), ' ');
        //cout <<  std::bitset<5>(1 << (n-1)) << "\n" ;
        result = transform(prev.begin(), prev.end(),
            result,
            [](const string& x) { return x + " " + x; });
            transform(prev.begin(), prev.end(),
            result,
            [sp](const string& x) { return sp + x + sp; });
    }
}

template<typename OutIt>
void sierpinskiUp(int n, OutIt result)
{
    if( n == 0 )
    {
        *result++ = "*";
    }
    else
    {
        list<string> prev;
        sierpinskiUp(n-1, back_inserter(prev));

        string sp(1 << (n-1), ' ');
        //cout <<  std::bitset<5>(1 << (n-1)) << "\n" ;
        result = transform(prev.begin(), prev.end(),
            result,
            [sp](const string& x) { return sp + x + sp; });
        transform(prev.begin(), prev.end(),
            result,
            [](const string& x) { return x + " " + x; });
    }
}

template<typename OutIt>
void sierpinskiHazardDown(int n, OutIt result)
{
    if( n == 0 )
    {
        *result++ = "*";
    }
    else
    {
        list<string> prev;
        sierpinskiUp(n-1, front_inserter(prev));

        string sp(1 << (n-1), ' ');
        //cout <<  std::bitset<5>(1 << (n-1)) << "\n" ;
        result = transform(prev.begin(), prev.end(),
            result,
            [sp](const string& x) { return sp + x + sp; });
        transform(prev.begin(), prev.end(),
            result,
            [](const string& x) { return x + " " + x; });
    }
}
 
int main(int argc, char ** argv)
{
    string userSays; 
    if(argc >= 2)
        userSays = argv[1];

    runAgain:
    srand(time(NULL));
    sierpinskiDwn(rand() % 5, ostream_iterator<string>(cout, "\n"));
    sierpinskiUp(rand() % 5, ostream_iterator<string>(cout, "\n"));
    sierpinskiHazardDown(rand() % 5, ostream_iterator<string>(cout, "\n"));
    sierpinskiHazardUp(rand() % 5, ostream_iterator<string>(cout, "\n"));

    
    if(userSays == "")
    {
        std::cout << "Run again? [y/n]: "; 
        cin >> userSays;
    }

    if(userSays == "y" || userSays == "Y")
        goto runAgain;
    else 
        return 0;
}