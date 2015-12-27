#include <iostream>

using namespace std;

bool z = false;

void SetIndividualFlag(bool* flagToSet)
{
    *flagToSet = (*flagToSet == true) ? false : true;
}
 
void SetIndividualFlag(bool& flagToSet)
{
    flagToSet = (flagToSet == true) ? false : true;
}
 
int main() 
{
    bool x = 1;
    bool * xp = &x;
    //cout << "(*xp): " << (*xp) << "\n";
    SetIndividualFlag(&z);
    cout << "z after setting individual flag called with pointer: " << z << "\n";
    SetIndividualFlag(z);
    cout <<  "z after setting individual flag called with ref: " << z << "\n";
 
    return 0;
}