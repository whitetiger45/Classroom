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
func(SubMenu, "\nWhat would you like to do?\n_______________________________\n\n1) Guess Letter\n2) Guess Word\n3) See what letters you've guessed\n4) Show Unfinished Word\n5) How Many Incorrect Guesses Left?\n6) Display HangMan Board\n7) Exit App\n_______________________________\n")
#undef func

#define func(n,a) void ask##n(){std::cout << a << "\n";}
func(ForLetter, "\nWhat letter would you like to guess?\n(Enter 1 to go back to main menu)")
func(PlayAgain, "Would you like to play again? [n/y]: ")
func(ForSuspectedWord, "What do you think the word is?")
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
    int getWordAtLocation = 0, correctOrSameGuessCounter = 0, userSubMenuResponseI = 0;
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
            main_menu:
            if(guess.getTriesLeft() == 0)
            {
                goto outOfTries;
            }
            const char * userGuessWord;//[guess.getWord().size()];
            bool guessSingleChar = true, userGuessedRightWord = false;
            showSubMenu();
            string userSubMenuResponse_str;
            cout << "User: "; cin >> userSubMenuResponse_str;
            while(!isdigit(userSubMenuResponse_str[0]))
            {
                cout << "\nYou must enter a valid menu option (1-7)\n";
                showSubMenu(); cout << "User: "; cin >> userSubMenuResponse_str;
            }
            userSubMenuResponseI = stoi(userSubMenuResponse_str);
            switch(userSubMenuResponseI)
            {
                case 1:
                {
                    caseOneStart:
                    string userGuess_str;
                    int userGuess_i = 1;
                    askForLetter();
                    cout << "\n";
                    cout << "Word: " << guess.incompleteWord() <<  "\n";
                    lineWrapper(string("\nGuessed letters: [" + guess.getGuessedLetters() +  "]"), '~');
                    cout << "Guessed letters: [" << guess.getGuessedLetters() <<  "]\n";
                    lineWrapper(string("\nGuessed letters: [" + guess.getGuessedLetters() +  "]"), '~');
                    cout << "U: "; cin >> userGuess_str;
                    if(isdigit(userGuess_str[0]))
                    {
                        userGuess_i = stoi(userGuess_str);
                        if(userGuess_i == 1)
                            goto main_menu;
                        else
                            goto caseOneStart;
                    }
                    else if(userGuess_str.size() > 1)
                    {
                        cout << "\n**You entered more than one character...please enter only one letter**\n";
                        goto caseOneStart;
                    }
                    else
                        userGuess[0] = userGuess_str[0];
                    break;
                }
                case 2:
                {
                    caseTwoStart:
                    guessSingleChar = false;
                    lineWrapper(string("\nUnfinished word: " + string(guess.showWord()) + "\n"), '*');
                    cout << "Unfinished word: " << guess.showWord() << "\n";

                    lineWrapper(string("\nGuessed letters: [" + guess.getGuessedLetters() +  "]"), '-');
                    cout << "Guessed letters: [" << guess.getGuessedLetters() << "]\n";
                    lineWrapper(string("\nGuessed letters: [" + guess.getGuessedLetters() +  "]"), '*');
                    cout << "\n";

                    askForSuspectedWord();
                    cin.ignore(); cout << "Enter the full word (Enter 1 to go back to main menu): ";
                    string userGuessWord_str;
                    cin >> userGuessWord_str;
                    if(isdigit(userGuessWord_str[0]))
                    {
                        int userGuessWord_i = stoi(userGuessWord_str);
                        if(userGuessWord_i == 1)
                            goto main_menu;
                        else
                            goto caseTwoStart;
                    }
                    else if(ispunct(userGuessWord_str[0]))
                    {
                        cout <<  "\n**You entered something that doesn't make sense...**\n";
                        goto caseTwoStart;
                    }
                    else
                        //cin.getline(userGuessWord, 256);
                        userGuessWord = userGuessWord_str.c_str();
                    for(auto c : userGuessWord_str)
                    {
                        bool alreadyGuessed = false;
                        if(!isalpha(c))
                          continue;
                        for(auto w : string(guess.getGuessedLetters()))
                        {
                            if(w == c)
                            {
                                alreadyGuessed = true;
                                break;
                            }
                        }
                        if(alreadyGuessed)
                        {
                            continue;
                        }
                        else if(!guess.guessLetter(c))
                        {
                            guess.subtractTry();
                        }
                        if(guess.getTriesLeft() == 0)
                        {
                          break;
                        }
                    }
                    if(guess.showWord() == guess.getWord() && userGuessWord == guess.getWord())
                    {
                        userWonRound = true;
                        userGuessedRightWord = true;
                        endOfRoundMessage(declareUserWinsRound);
                        goto userDiscoveredTheWord;
                    }
                    //cout << "\nGuessed word: " << userGuessWord << ", actual word: " << guess.getWord() << "\n";
                    if(guess.getTriesLeft() != 0 && guess.showWord() != guess.getWord())
                    {
                        cout << "\nYou didn't get the word correct, but you got some letters correct...keep going!\n";
                        cout << "Unfinished word: " ;
                        for(auto c : string(guess.showWord()))
                            cout << c << " ";
                        cout << "\n"; 
                        goto main_menu;
                    }
                    else if(guess.getTriesLeft() == 0)
                        break;
                }
                case 3:
                {
                    cout << "\n";
                    lineWrapper(string("\nGuessed letters: [" + guess.getGuessedLetters() +  "]"), '~');
                    cout << "Guessed letters: [" << guess.getGuessedLetters() <<  "]\n";
                    lineWrapper(string("\nGuessed letters: [" + guess.getGuessedLetters() +  "]"), '~');
                }
                case 4:
                {
                    lineWrapper(string("Incomplete Word: " + string(guess.incompleteWord()) + "\n"), '~');
                    cout << "Incomplete Word: ";
                    for(auto c : string(guess.showWord()))
                        cout << c << " ";
                    cout << "\n"; 
                    lineWrapper(string("Incomplete Word: " + string(guess.incompleteWord()) + "\n"), '~');
                }
                case 5:
                {
                    lineWrapper(string("Tries left: " + to_string(guess.getTriesLeft()) + "\n"), '~');
                    cout << "Tries left: " << guess.getTriesLeft() << "\n";
                    lineWrapper(string("Tries left: " + to_string(guess.getTriesLeft()) + "\n"), '~');
                    cout << "\n";
                    goto main_menu;    
                }
                case 6:
                {
                    guess.displayHangMan();
                    cout << "\n";
                    goto main_menu;
                }
                case 7:
                {
                    goto quit;
                }
                default:
                {
                    cout << "\nYou must enter a valid option (1-7)\n";
                    goto main_menu;
                }
            }
            if(guess.getTriesLeft() == 0 || userWonRound)
                break;
            while((!isalpha(userGuess[0]) || string(userGuess).size() > 1) && guessSingleChar)
            {
                correctOrSameGuessCounter++;
                if(correctOrSameGuessCounter == 5)
                {
                  guess.displayHangMan();
                  correctOrSameGuessCounter = 0;
                }
                if(string(userGuess).size() > 1)
                    cout << "You entered more than one letter...please follow instructions.\n";
                else
                    cout << "You entered something that doesn't make sense.\n";
                askForLetter();
                cout << "Enter a letter: "; cin >> userGuess;
            }
            if(!guess.guessLetter(userGuess[0]) && guessSingleChar)
            {
                guess.subtractTry();
                guess.displayHangMan();
                lineWrapper(string("\nGuessed letters: [" + guess.getGuessedLetters() +  "]"), '*');
                cout << "Guessed letters: [" << guess.getGuessedLetters() <<  "]\n";
                lineWrapper(string("\nGuessed letters: [" + guess.getGuessedLetters() +  "]"), '*');
            }
            else
                correctOrSameGuessCounter++;

            if(correctOrSameGuessCounter == 5)
            {
                guess.displayHangMan();
                correctOrSameGuessCounter = 0;
            }
            std::cout << "\nWord: " ;
            for(auto c : string(guess.showWord()))
                cout << c << " ";
            cout << "\n";
            if(guess.showWord() == guess.getWord())
            {
                userWonRound = true;
                endOfRoundMessage(declareUserWinsRound);
            }
        }while(guess.getTriesLeft() != 0 && !userWonRound);
        outOfTries:
        if(guess.getTriesLeft() == 0)
        {
            endOfRoundMessage(declareOutOfGuesses);
        }
        userDiscoveredTheWord:
        raise(SIGINT);
        cout << guess.getWord() << "\n";
        askPlayAgain();
        cin >> userResponse;
        if(isupper(userResponse[0]))
            userResponse[0] = tolower(userResponse[0]);
        while(!isalpha(userResponse[0]) || (userResponse[0] != 'n' && userResponse[0] != 'y') || (string(userResponse).size() > 1))
        {
            if(string(userResponse).size() > 1)
                cout << "You entered more than one letter...please follow instructions.\n";
            else
                cout << "You did not enter a valid response!\n";
            askPlayAgain();
            cin >> userResponse;
            if(isupper(userResponse[0]))
                userResponse[0] = tolower(userResponse[0]);
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
    quit:
    guess.getMostFrequentLetterFromDictionaryWord();
    guess.getFirstGuessAccuracy();
    return 0;
}