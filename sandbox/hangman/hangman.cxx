#include <csignal>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <typeinfo>

#include "hangman.hxx"

#define func(n, a) void show##n(){std::cout << a << "\n";}
func(Menu, "**********\nH        *\n a       *\n  n      *\n   g     *\n    m    *\n     a   *\n      n  *\n**********")
#undef func

#define func(n,a) void ask##n(){std::cout << a << "\n";}
func(ForLetter, "What letter would you like to guess: ")
func(PlayAgain, "Would you like to play again? [n/y]: ")
#undef func

sig_atomic_t userScore = 0;
sig_atomic_t totalGames = 0;

#define func(n, a, b, c) void declare##n(int param){std::cout << a ; ++b; ++c;}
func(UserWinsRound, "You win!\nThe correct word was: ", userScore, totalGames)
#undef func

#define func(n, a, b) void declare##n(int param){std::cout << a ; ++b;}
func(OutOfGuesses, "Sorry, you are out of guesses...\nThe correct word was: ", totalGames)
#undef func

#define func(n, a, b) void score##n(){ std::cout << std::fixed << "\nWins | Total Games Played This Round  |     Win Percentage    \n  " << a << "  |            " << b << "                   |           " << std::setprecision(2) <<(double(double(a)/double(b)) * 100) << "\%      \n";}
func(Board, userScore, totalGames)

//todo: 
//look into passing a string with the word to the function so it outputs the word in the same method that updates the scoreboard
// int call_a_func(MathFunc call_this, int x, int y) 
// {
//     float output = call_this(x, y);
//     return output;
// }
// int final_result = call_a_func(&mul, a, b);
// cout<< a << " * " << b << " = " << final_result << "\n";


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
    int getWordAtLocation = 0, correctOrSameGuessCounter = 0;
    void (*result_handler)(int);
    showMenu();
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
          else
            correctOrSameGuessCounter++;
          if(correctOrSameGuessCounter == 5)
          {
            guess.displayHangMan();
            correctOrSameGuessCounter = 0;
          }
       		std::cout << "\nWord: " << guess.showWord();
       		std::cout<< "\nGuessed letters: " << guess.getGuessedLetters() << "\n";
       		if(guess.showWord() == guess.getWord())
       		{
       			//cout << "Correct!\nWord: "<< guess.getWord() << "\n";
                userWonRound = true;
                result_handler = signal(SIGINT, declareUserWinsRound);
                //cout << guess.getWord();
       		}
   	    }while(guess.getTriesLeft() != -1 && !userWonRound);

	   	if(guess.getTriesLeft() == -1)
	   	{
	   		//cout << "You are out of guesses, the word was: ";
            result_handler = signal(SIGINT, declareOutOfGuesses);
	   	}
        raise(SIGINT);
        cout << guess.getWord();
	    std::cout<<"\n";
	    askPlayAgain();
        cin >> userResponse[0];
        while(!isalpha(userResponse[0]) || (userResponse[0] != 'n' && userResponse[0] != 'y'))
        {
            cout << "You did not enter a valid response!\n";
            askPlayAgain();
            cin >> userResponse[0];
        }
	    playAgain = (userResponse[0] == response[n]) ? false : true;
        if(playAgain)
        {
            guess.resetTries();
            correctOrSameGuessCounter = 0;
            userWonRound = false;
        }
	}while(playAgain);
    scoreBoard();
    return 0;
}