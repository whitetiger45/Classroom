#include <iostream>
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
        enum {eb, ec};
        int get = (val == "b") ? eb : ec;
        switch(get)
        {
            case eb:
                return b;
            case ec:
                return c;
        }
        return c;
    }
 
    private: 
    bool b = false;
    bool c = true;
};
  
int main() 
{
    test s;
    test* sp = &s;
    cout << "GetVal c: " << sp->getVal("c") << "\nGetVal b: " << sp->getVal("b") << "\n";
    sp->SetIndividualFlag( sp->getVal("c"));
    cout << "c after flag set 1: " << sp->getVal("c") << "\n";
    sp->SetIndividualFlag( sp->getVal("c"));
    cout << "c after flag set 2: " << sp->getVal("c") << "\n";
    sp->SetIndividualFlag( sp->getVal("b"));
    cout << "b after flag set 1: " << sp->getVal("b") << "\n";
    
    return 0;
}