#include <iostream>
#include <map>
#include <string>
#include <ctime>
#include <cstdlib>
#include <iterator>

using namespace std;

int main ()
{
    std::srand(std::time(nullptr));
    std::multimap<std::string, int> mymm;

    mymm.emplace("Hello", 50);
    mymm.emplace("Bye",  100);
    mymm.emplace("Bye",  150);
    mymm.emplace("Bye",  200);
    mymm.emplace("?",    250);
    mymm.emplace("?",    300);

    auto range = mymm.equal_range("Bye");
    auto count = std::distance(range.first, range.second);
    if (count != 0) {
        auto it = std::next(range.first, std::rand() % count);
        std::cout << it -> second << endl;
    }
}