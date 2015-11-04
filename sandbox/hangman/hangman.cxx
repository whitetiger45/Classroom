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

using namespace std;

int main() 
{
	word guess;
	string line;
  	ifstream dictionaryFile ("dictionary.txt");
  	srand(time(NULL));
  	int count = 1;
  	int getWordAtLocation = rand() % 173139;
  	if (dictionaryFile.is_open())
  	{
		while ( getline (dictionaryFile,line) && count != getWordAtLocation)
		{	
			count++;
		}
		guess.setWord(line);
		dictionaryFile.close();
	}

   	//guess.setWord("hello");
   	guess.guessLetter('a');
   	//std::cout << "\nWord: " << guess.showWord();
    std::cout<<"\n";
   	do{
   		askForLetter();
		char userGuess[1];
		cin >> userGuess;
   		if(!guess.guessLetter(userGuess[0]))
	   		guess.printHangMan();
   		std::cout << "\nWord: " << guess.showWord();
   		std::cout<< "\nGuessed letters: " << guess.getGuessedLetters() << "\n";
   		if(guess.showWord() == guess.getWord())
   		{
   			cout << "Correct!\nWord: "<< guess.getWord() << "\n";
   		}
   	}while(guess.getTriesLeft() != -1);

   	if(guess.getTriesLeft() == -1)
   	{
   		cout << "You are out of guesses, the word was: " << guess.getWord();
   	}
    std::cout<<"\n";
   
    return 0;
}