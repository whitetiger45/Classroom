//Incomplete
#include <cstdlib>
#include <iostream>
#include <vector>
 
using namespace std;
 
vector<vector<int>> board(3, vector<int>(1));
 
enum{X=1, O=-1, EMPTY=0};
 
void printBoard()
{
    for(int i = 0; i < 3; i++)
    {
        for(int l = 0; l < 3; l++)
        {
            switch(board[i][l])
            {
                case X: cout<<"X"; break;
                case O: cout <<"O"; break;
                case EMPTY: cout <<" "; break;
            }
            if (l < 2) cout <<" | "; // column boundary
        }
        if (i < 2) cout <<"\n+-+-+-+-+-\n" ;
    }
}
 
 
int main() 
{
 
    printBoard(); 
    cout << "\n";  
 
    return 0;
}