#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <typeinfo>

#include "hangman.hxx"

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
   	//do{
   	//	guess.printHangMan();
   	//}while(guess.getTriesLeft() != -1);
   	guess.guessLetter('e');
   	//std::cout << "\nWord: " << guess.showWord();
    std::cout<<"\n";
   	guess.guessLetter('i');
   	std::cout << "\nWord: " << guess.showWord();
    std::cout<<"\n";
    std::cout<< "Guessed letters: " << guess.getGuessedLetters() << "\n";

    return 0;
}