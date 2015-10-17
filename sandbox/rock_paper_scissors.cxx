#include <cstdlib>
#include <ctime>
#include <iostream>
#include <csignal>
#include <string>

#define func(n,a) void me##n() { std::cout << a;} 
func(nu, "Enter rock, paper or scissors: ")
#undef func
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
    
    menu();
    string userChoice;
    cin >> userChoice;
    srand(time(NULL));
    cout << "User: "<< userChoice <<"\nComputer: " << choice[rand() % 18] << "\n";


    return 0;
}