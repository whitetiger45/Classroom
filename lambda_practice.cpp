#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    auto func = []() {cout << "\nHello World\n\n";};

    auto func2 = []()-> int {return 1;}; 

    func();
    cout<< "\n\nFunc2: " << func2 << "\n\n";

    vector<int> v;
    vector<int> T;
    v.push_back( 1 );
    v.push_back( 2 );
    v.push_back( 3 );
    v.push_back( 4 );
    v.push_back( 5 );
    v.push_back( 6 );    
    //...
    for_each( v.begin(), v.end(), [](int val)->int {return val;});

    auto count = 0;
    auto a = [](int v){return v * 9;};
     for(auto t : v)
        T.push_back(a(t));

    for(auto t : T)
        cout<<++count << ": " <<  t << "\n";
    
     [] { cout << "\nHello, my Greek friends\n\n"; }();

     auto num = [](){ ;};
}