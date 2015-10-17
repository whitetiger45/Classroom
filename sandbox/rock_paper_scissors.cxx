#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

using namespace std;

string choice[] = {"rock", "paper", "scissors"
, "paper","rock", "scissors"
, "scissors", "rock", "paper"
, "scissors", "paper", "rock"
, "rock", "scissors", "paper"
, "paper", "scissors", "rock"};
enum {rock, paper, scissors};

int main()
{
    srand(time(NULL));
    cout << choice[rand() % 18] << "\n";
    return 0;
}