#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <typeinfo>

#include "hangman.hxx"

#define func(n,a) void ask##n(){std::cout << a << "\n";}
func(ForLetter, "What letter would you like to guess: ")
func(PlayAgain, "Would you like to play again? [n/y]: ")
#undef func

char response[] = {'n', 'y'};
enum {n, y};
using namespace std;

int main() 
{
	word guess;
	string line;
    bool playAgain = false;
    bool userWonRound = false;
    char userResponse[1];
    char userGuess[1];
    int getWordAtLocation = 0;
    do
    { 
      	int count = 1;
        srand(time(NULL));
      	getWordAtLocation = rand() % 173139;
        ifstream dictionaryFile ("dictionary.txt");
      	if(dictionaryFile.is_open())
      	{
    		while ( getline (dictionaryFile,line) && count != getWordAtLocation)
    		{	
    			count++;
    		}
    		guess.setWord(line);
            dictionaryFile.close();
    	}
    	do{
       		askForLetter();
            cin >> userGuess[0];
       		if(!guess.guessLetter(userGuess[0]))
    	   		guess.printHangMan();
       		std::cout << "\nWord: " << guess.showWord();
       		std::cout<< "\nGuessed letters: " << guess.getGuessedLetters() << "\n";
       		if(guess.showWord() == guess.getWord())
       		{
       			cout << "Correct!\nWord: "<< guess.getWord() << "\n";
                userWonRound = true;
       			//askPlayAgain();
        		//cin.ignore(); cin.getline(userResponse, 1);
       			//playAgain = (userResponse[0] == response[n]) ? false : true;
       		}
   	    }while(guess.getTriesLeft() != -1 && !userWonRound);

	   	if(guess.getTriesLeft() == -1)
	   	{
	   		cout << "You are out of guesses, the word was: " << guess.getWord();
	   	}
	    std::cout<<"\n";
	    askPlayAgain();
        cin >> userResponse[0];
	    playAgain = (userResponse[0] == response[n]) ? false : true;
        if(playAgain)
        {
            guess.resetTries();
            userWonRound = false;
        }
	}while(playAgain);
    return 0;
}