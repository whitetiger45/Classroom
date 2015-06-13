#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
 
using namespace std;
 
 
int main() 
{
    srand(time(NULL));
    vector< vector<int> > X (3, vector<int>(1));
 
    for(int i = 0; i != X.size(); i++)
    {
        // cout << i << ") ";
        for(int l = 0; l <= X.size() ; l++)
        {
            if(i == (X.size()-1))
            {
                cout<< X[i-1][l] + (rand() % 10) * 2;
            }
 
            else
                cout << X[i][l] +  (rand() % 10) * 2;
 
            if(l != (X.size()))
            {
                cout << " ";
            }
        }
 
        cout <<"\n";
    }
    return 0;
}