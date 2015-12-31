#include <iostream>
#include <map>
using namespace std;
 
class test
{
public:

    void SetIndividualFlag(bool& flagToSet)
    {
       flagToSet = (flagToSet == true) ? false : true;
    }
 
    bool& getVal(std::string val)
    {
        return m.find(val)->second;
    }
 
private: 
    map<string, bool> m = {{"a", true}, {"b", true}, {"c", false}, {"not found", false}};
    map<string, bool>::iterator mit;
};
  
int main() 
{
    test s;
    test* sp = &s;
    cout << "GetVal c: " << sp->getVal("c") << "\n";
    sp->SetIndividualFlag( sp->getVal("c"));
    cout << "c after set flag: " << sp->getVal("c") << "\n";
    cout << "GetVal a: " << sp->getVal("a") << "\n";
    sp->SetIndividualFlag( sp->getVal("a"));
    cout << "a after set flag: " << sp->getVal("a") << "\n";
    cout << "checking for flag that doesnt exist: " << sp->getVal("f") << "\n";

    
    return 0;
}