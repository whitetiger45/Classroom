#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>
#include <typeinfo>

#include "hangman.hxx"

using namespace std;

int main() 
{
	word guess;

   	guess.setWord("hello");
   	guess.guessLetter('l');
   	std::cout << "\nWord: " << guess.showWord();
    std::cout<<"\n";
   	do{
   		guess.printHangMan();
   	}while(guess.getTriesLeft() != -1);

    return 0;
}