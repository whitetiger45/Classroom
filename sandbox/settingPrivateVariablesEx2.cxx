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
        for(mit = m.begin(); mit != m.end(); mit++)
            if(mit->first == val)
                return mit->second;
    }
 
private: 
    map<string, bool> m = {{"a", true}, {"b", true}, {"c", false}};
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

    
    return 0;
}