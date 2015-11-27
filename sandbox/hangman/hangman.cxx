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
func(Title, "**********\nH        *\n a       *\n  n      *\n   g     *\n    m    *\n     a   *\n      n  *\n**********")
func(Menu, "***Main Menu***\n1: Start\n2: Scoreboard")
#undef func

#define func(n,a) void ask##n(){std::cout << a << "\n";}
func(ForLetter, "What letter would you like to guess: ")
func(PlayAgain, "Would you like to play again? [n/y]: ")
#undef func

sig_atomic_t userScore = 0;
sig_atomic_t totalGames = 0;

#define func(n, a, b, c) void declare##n(int param){std::cout << a ; ++b; ++c;}
func(UserWinsRound, "\n\t**********\n\t*You win!*\n\t**********\n\nThe correct word was: ", userScore, totalGames)
#undef func

#define func(n, a, b) void declare##n(int param){std::cout << a ; ++b;}
func(OutOfGuesses, "Sorry, you are out of guesses...\nThe correct word was: ", totalGames)
#undef func

#define func(n, a, b) void score##n(){ std::cout << std::fixed << "\nWins | Total Games Played This Round  |     Win Percentage    \n  " << a << "  |            " << b << "                   |           " << std::setprecision(2) <<(double(double(a)/double(b)) * 100) << "\%      \n";}
func(Board, userScore, totalGames)

void (*result_handler)(int);
typedef void (*getResultFunc)(int);

void endOfRoundMessage(getResultFunc result)
{
    result_handler = signal(SIGINT, result);
}

auto lineWrapper = [](std::string lineToWrap, char c){for(int i = 0; i < lineToWrap.size(); i++)std::cout << c; std::cout << "\n";};
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
    showTitle();
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
            cin >> userGuess;
          while(!isalpha(userGuess[0]) || string(userGuess).size() > 1 )
          {
            if(string(userGuess).size() > 1)
                cout << "You entered more than one letter...please follow instructions.\n";
            else
                cout << "You entered something that doesn't make sense.\n";
            askForLetter();
            cin >> userGuess;
          }
            if(!guess.guessLetter(userGuess[0]))
            {
                guess.subtractTry();
                guess.displayHangMan();
            }
            else
                correctOrSameGuessCounter++;
          if(correctOrSameGuessCounter == 5)
          {
            guess.displayHangMan();
            correctOrSameGuessCounter = 0;
          }
                for(auto c : string(guess.showWord()))
                    cout << c << " ";
                cout << "\n";
                lineWrapper(string("Guessed letters: [" + guess.getGuessedLetters() + "]\n"), '~');
        		std::cout<< "Guessed letters: [" << guess.getGuessedLetters() << "]\n";
                lineWrapper(string("Guessed letters: [" + guess.getGuessedLetters() + "]\n"), '~');
        		if(guess.showWord() == guess.getWord())
        		{
                userWonRound = true;
                endOfRoundMessage(declareUserWinsRound);
        		}
            }while(guess.getTriesLeft() != 0 && !userWonRound);

        	if(guess.getTriesLeft() == 0)
        	{
                endOfRoundMessage(declareOutOfGuesses);
        	}
        raise(SIGINT);
        cout << guess.getWord() << "\n";
        askPlayAgain();
        cin >> userResponse;
        while(!isalpha(userResponse[0]) || (userResponse[0] != 'n' && userResponse[0] != 'y') || (string(userResponse).size() > 1))
        {
            if(string(userResponse).size() > 1)
                cout << "You entered more than one letter...please follow instructions.\n";
            else
                cout << "You did not enter a valid response!\n";
            askPlayAgain();
            cin >> userResponse;
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