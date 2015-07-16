//Author: Bryan Kanu
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
 
int main()
{
    std::vector<int> c { 1,2,3,4,5,6,7 };
    std::vector<int> d { 10, 20, 30, 40, 50 };
    std::vector<int> e;
    int x = 5;
 
    // auto check = [](int n, int x) { return n > x; };
    auto check2 = [](int n, std::vector<int> x,  std::vector<int> y ) 
    { 
        for(auto i: x)
        { 
            for(auto l: y)
                if((i*i) +  n > l) std::cout << i * i + n << " > " << l << "\n";
        } 
 
    };
 
    std::cout << "c: ";
    for (auto i: c) {
        check2(i, c, d) ;
    }
    std::cout << '\n';
 
}