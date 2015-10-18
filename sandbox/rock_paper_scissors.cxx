#include <cstdlib>
#include <ctime>
#include <iostream>
#include <csignal>
#include <string>

#define func(n,a) void me##n() { std::cout << a;} 
func(nu, "Enter rock, paper or scissors: ")
#undef func
#define func(n, a) void ask##n() { std::cout << a;}
func(PlayAgain, "Would you like to play again? [y or n]: ")
using namespace std;

char opts[] = {'n', 'y'};
string choice[] = {"rock", "paper", "scissors"
, "paper","rock", "scissors"
, "scissors", "rock", "paper"
, "scissors", "paper", "rock"
, "rock", "scissors", "paper"
, "paper", "scissors", "rock"};
enum {rock, paper, scissors};
enum {n, y};


int main()
{
    bool playAgain = true;
    char userWantsToPlayAgain;
    do
    {
        menu();
        string userChoice;
        cin >> userChoice;
        srand(time(NULL));
        cout << "User: "<< userChoice <<"\nComputer: " << choice[rand() % 18] << "\n";
        askPlayAgain();
        std::cin >> userWantsToPlayAgain;
        playAgain = (userWantsToPlayAgain == opts[n]) ? false : true;
    }while(playAgain);



    return 0;
}