#include <iostream>
using namespace std;
#define WIDTH 5
#define HEIGHT 5

char hello [HEIGHT][WIDTH];
char world [HEIGHT][WIDTH];
char word1 [] = { 'h', 'e', 'l', 'l', 'o'};
char word2 [] = {'w', 'o', 'r', 'l', 'd'};
int n,m;

int main ()
{
  for (n=0; n<HEIGHT; n++)
    for (m=0; m<WIDTH; m++)
    {
      if(n == m)
        hello[n][m]= word1[n];
    }
  
    for (n=HEIGHT; n >=0; n--)
        for (m=WIDTH; m >=0; m--)
        {
          if(n == m)
            world[n][m]= word2[m];
        }
    
    
  for (n=0; n<HEIGHT; n++)
  {
    for (m=0; m<WIDTH; m++)
    {
      std::cout << hello[n][m] << " ";
    }
     std::cout << "\n";
  }
  
  for (n=0; n !=HEIGHT; n++)
  {
    for (m=WIDTH; m>=0; m--)
    {
      std::cout << world[n][m] << " ";
    }
     std::cout << "\n";
  }
}
