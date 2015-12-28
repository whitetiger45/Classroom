#include <iostream>
using namespace std;
      
bool z = false;
void SetIndividualFlag(bool* flagToSet)
{
    cout << "ptr version: ";
    *flagToSet = (*flagToSet == true) ? false : true;
}
 
void SetIndividualFlag(bool& flagToSet)
{
    cout << "reference version: ";
    flagToSet = (flagToSet == true) ? false : true;
}
 
int main() 
{
    bool x = true;
    bool * xp = &x;
    bool ** xpp = &xp;
    cout << "(*xp): " <<(*xp) << "\n";
    cout <<"(*xpp): " << (*xpp) << "\n";
    cout <<"*(*xpp): " << *(*xpp) << "\n";
    SetIndividualFlag(&z);
    cout <<"z: " << z << "\n";
    SetIndividualFlag(z);
    cout << "z: " <<z << "\n";
    SetIndividualFlag(*xpp);
    cout <<"*(*xpp): " << *(*xpp) << "\n";
    cout <<"&(*xpp): " << &(*xpp) << "\n";
    cout <<"*(&(*xpp)): " << *(&(*xpp)) << "\n";
    cout <<"**&(*xpp): " << **&(*xpp) << "\n";
 
    return 0;
}