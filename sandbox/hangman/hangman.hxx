#ifndef HANGMAN_HXX
#define HANGMAN_HXX

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#define func(n, a) void show##n(){std::cout << a << "\n";}
// func(Title, "**********\nH        *\n a       *\n  n      *\n   g     *\n    m    *\n     a   *\n      n  *\n**********")
func(Title, "\n\t   ***********\n\t   * Hangman *\n\t   ***********\n\t______\n\t|    |\n\t|    \n\t|           o\n\t|          /|\\ \n\t|______    / \\\n\t*****************\n")
func(Menu, "\n\t Main Menu\n\t =========    \n     1: Survival Mode\n     2: Regular Mode\n     3: Quit\n")
func(SubMenu, "\nWhat would you like to do?\n_______________________________\n\n1) Guess Letter\n2) Guess Word\n3) See what letters you've guessed\n4) Show Unfinished Word\n5) How Many Incorrect Guesses Left?\n6) Display HangMan Board\n7) Exit App\n_______________________________\n")
#undef func

#define func(n,a) void ask##n(){std::cout << a << "\n";}
func(ForLetter, "\nWhat letter would you like to guess?\n(Enter 1 to go back to main menu)")
func(PlayAgain, "\n(Type 's' to see your current stat)\nPlay again? [n/y/s]: ")
func(ForSuspectedWord, "What do you think the word is?")
#undef func

//------------------------------------------------------------------------------------------------------------------------
//scoreboard stuff
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
//------------------------------------------------------------------------------------------------------------------------

typedef std::vector<std::string> HangmanDictionary;
typedef	std::map<char,int> LetterTrackingMap;
typedef std::map<char,int>::iterator LetterTrackingMapIT;

auto lineWrapper = [](std::string lineToWrap, char c){for(int i = 0; i < lineToWrap.size(); i++)std::cout << c; std::cout << "\n";};

class word
{
	public: 
		
		void setWord(std::string value)
		{
			m_guessCount = 0;
			m_guessedLetters[0] = '\0';
	  		std::size_t length = value.copy(m_word, value.length(), 0);
  			m_word[length]='\0';
  			m_wordLength = value.length();
			for(int i = 0; i < value.length(); i++)
				m_incompleteWord[i] = '_' ;

			m_incompleteWord[length] = '\0';

	        trackDictionaryLetters(value);
	        m_numberOfGames++;
		}

		const char* showWord() const
		{
			return m_incompleteWord;
		}

		std::string incompleteWord() const
		{
			std::string ret;
			for(auto c : std::string(m_incompleteWord))
			{
				ret = ret + " " + c;
			}
			return ret;
		}

		bool guessLetter(char value)
		{
			if(isupper(value))
				value = tolower(value);

			if( getGuessedLetters() == "" )
			{
				trackFirstGuessAccuracy(value);
			}

			bool letterFound = false;

			for(int i = 0; i < m_wordLength; i++)
			{
				if(m_word[i] == value)
				{
					m_incompleteWord[i] = value;
					letterFound = true;
				}
			}

			for(int i = 0; i < m_guessCount; i++)
				if(m_guessedLetters[i] == value)
				{
					std::cout << "\nYou already guessed that letter!\n";
					return true;
				}

			m_triesLeft = (letterFound) ? m_triesLeft : m_triesLeft--;
			addCharToGuessedLetters(value);

			return letterFound;
		}

		std::string getGuessedLetters() const
		{
			return m_guessedLetters;
		}

		void addCharToGuessedLetters(char value)
		{
			m_guessedLetters[m_guessCount++] = value;
			m_guessedLetters[m_guessCount] = '\0'; 
		}

		std::string getWord() const
		{
			return m_word;
		}

		int getTriesLeft() const
		{
			return m_triesLeft;
		}

		void subtractTry()
		{
			m_triesLeft--;
		}

		void resetTries()
		{
			m_triesLeft = 6;
			for(auto x : m_guessedLetters)
				x = ' ';
		}

		void displayHangMan()
		{
			    switch(m_triesLeft)
			    {
			    	case 6:
    					    std::cout<< " ______\n";
							std::cout<< "|    |\n|    \n|     \n|           \n|______\n";
							break;
			    	case 5:
    					    std::cout<< " ______\n";
							std::cout<< "|    |\n|    o\n|     \n|          \n|______\n";
							break;
			    	case 4:
    					    std::cout<< " ______\n";
							std::cout<< "|    |\n|    o\n|    |\n|          \n|______\n";
							break;
			    	case 3:
    					    std::cout<< " ______\n";
							std::cout<< "|    |\n|    o\n|   /|\n|          \n|______\n";
							break;
			    	case 2:
    					    std::cout<< " ______\n";
							std::cout<< "|    |\n|    o\n|   /|\\ \n|        \n|______\n";
							break;
			    	case 1:
    					    std::cout<< " ______\n";
							std::cout<< "|    |\n|    o\n|   /|\\\n|   /     \n|______\n";
							break;
					case 0:
						    std::cout<< " ______\n";
    						std::cout<< "|    |\n|    o\n|   /|\\\n|   / \\  \n|______\n";
    						break;
					default:
						    std::cout<< " ______\n";
    						std::cout<< "|    |\n|    o\n|   /|\\\n|   / \\  \n|______\n";
			    }
		}

		void trackDictionaryLetters(std::string dictionaryWord)
		{
			    dictionaryWordLettersMapIT = dictionaryWordLettersMap.begin();
		        for(auto c: dictionaryWord)
		        {
		            dictionaryWordLettersMapIT = dictionaryWordLettersMap.find(c);
		            if(dictionaryWordLettersMapIT != dictionaryWordLettersMap.end())
		            {
		                dictionaryWordLettersMapIT->second++;
		            }
		            else
		                dictionaryWordLettersMap[c] = 1;
		             
		            if(dictionaryWordLettersMapIT->second > dictionaryLettersMapmostFrequentCount)
		                dictionaryLettersMapmostFrequentCount = dictionaryWordLettersMapIT->second;
		        }
		}

        std::string getMostFrequentLetterFromDictionaryWord()
        {
        	std::string ret;
           for(dictionaryWordLettersMapIT = dictionaryWordLettersMap.begin(); dictionaryWordLettersMapIT != dictionaryWordLettersMap.end(); dictionaryWordLettersMapIT++)
           {
               if(dictionaryWordLettersMapIT->second == dictionaryLettersMapmostFrequentCount)
               {
                   ret = "\nMost frequent letter(s) to appear in the dictionary words this session: ";
                   ret+= dictionaryWordLettersMapIT->first;
                   ret+= "\n# of times it appeard: " + std::to_string(dictionaryWordLettersMapIT->second) + "\n";
               }
           }
           return ret;
        }

		void printMostFrequentLettersFromDictionaryWord()
		{
		    for(dictionaryWordLettersMapIT = dictionaryWordLettersMap.begin(); dictionaryWordLettersMapIT != dictionaryWordLettersMap.end(); dictionaryWordLettersMapIT++)
		    {
		       if(dictionaryWordLettersMapIT->second == dictionaryLettersMapmostFrequentCount)
		           std::cout << "\nMost frequent letter(s) to appear in the dictionary words this session: " << dictionaryWordLettersMapIT->first << "\n# of times it appeard: " << dictionaryWordLettersMapIT->second << "\n";
		    }
		}

		int checkDictionaryMapLettersEqualToMaxCount()
		{
			int total = 0;
			for(dictionaryWordLettersMapIT = dictionaryWordLettersMap.begin(); dictionaryWordLettersMapIT != dictionaryWordLettersMap.end(); dictionaryWordLettersMapIT++)
				if(dictionaryWordLettersMapIT->second == dictionaryLettersMapmostFrequentCount)
					total++;
			return total;
		}

		void setFirstGuessWasCorrectValue()
		{
			m_firstGuessWasCorrect = true;
		}

		void trackFirstGuessAccuracy(char value)
		{
			std::map<int, std::string> firstGuessMessageMap;

			firstGuessMessageMap[0] = "\nExcellent start!\n";
			firstGuessMessageMap[1] = "\nGood guess!\n";
			firstGuessMessageMap[2] = "\nKeep it up!\n";
			firstGuessMessageMap[3] = "\nWow...nice!\n";
			m_m_firstGuessLettersMapIT = m_firstGuessLettersMap.begin();
			srand(time(NULL));

			for(auto c: getWord())
			{
			   if(value == c)
			   {			   
					m_letterWasInWord++;
					std::cout << firstGuessMessageMap[rand() % 4];
					setFirstGuessWasCorrectValue();
					break;
			   }
			}

		    m_m_firstGuessLettersMapIT = m_firstGuessLettersMap.find(value);

		    if(m_m_firstGuessLettersMapIT != m_firstGuessLettersMap.end())
		    {
		        m_m_firstGuessLettersMapIT->second++;
		    }
		    else
		        m_firstGuessLettersMap[value] = 1;
		     
		    if(m_m_firstGuessLettersMapIT->second > m_m_firstGuessLettersMapCount)
		        m_m_firstGuessLettersMapCount = m_m_firstGuessLettersMapIT->second;
		}

		void getFirstGuessAccuracy()
		{
			for(m_m_firstGuessLettersMapIT = m_firstGuessLettersMap.begin(); m_m_firstGuessLettersMapIT != m_firstGuessLettersMap.end(); m_m_firstGuessLettersMapIT++)
			{
				if(m_m_firstGuessLettersMapIT->second == m_m_firstGuessLettersMapCount)
				{
					std::cout << "\nMost frequent letter(s) to be guessed first: " << m_m_firstGuessLettersMapIT->first << "\nNumber of times guessed first: "<< m_m_firstGuessLettersMapIT->second<<"\n";
					std::cout << "\nFirst guess accuracy: " <<(m_letterWasInWord/m_numberOfGames) * 100 << "%\n\n";
				}
			}
		}

		void setMaxStreak(int currentStreak)
		{
			m_streak = currentStreak;
		}

		int getMaxStreak()
		{
			return m_streak;
		}

		bool checkIfFirstGuessWasCorrect() const
		{
			return m_firstGuessWasCorrect;
		}

		void resetFirstGuessWasCorrectValue()
		{
			m_firstGuessWasCorrect = false;
		}

		void incrementFirstGuessToWonRoundConversionTracker()
		{
			m_firstGuessToWonRoundConversionTracker++;
		}

		void getStats()
		{
			std::cout << std::endl; scoreBoard(); std::cout << std::endl;	

		    lineWrapper(getMostFrequentLetterFromDictionaryWord(), '=');

		    std::cout << "**Stats**\n";

		    if(checkDictionaryMapLettersEqualToMaxCount() == 1)
		        std::cout << getMostFrequentLetterFromDictionaryWord();
		    else
		        printMostFrequentLettersFromDictionaryWord();

		    getFirstGuessAccuracy();

		    std::cout << "# of times first guess was correct and user won the round: ";
		    std::cout << m_firstGuessToWonRoundConversionTracker << "\n";

		    std::cout << "Record streak: " << getMaxStreak() << "\n";

		    lineWrapper(getMostFrequentLetterFromDictionaryWord(), '=');
		}

	private:
		char m_word[256];
		char m_incompleteWord[256];
		char m_guessedLetters[26];
		int m_guessCount;
		int m_wordLength = 0;
		int m_roundsWon = 0;
		int m_streak = 0;
		signed int m_triesLeft = 6;
		HangmanDictionary m_dictionary;

	    LetterTrackingMap dictionaryWordLettersMap;
	    LetterTrackingMapIT dictionaryWordLettersMapIT;
	    int dictionaryLettersMapmostFrequentCount = 1;

	    LetterTrackingMap m_firstGuessLettersMap;
	    LetterTrackingMapIT m_m_firstGuessLettersMapIT;
	    bool m_firstGuessWasCorrect = false;
	    int m_m_firstGuessLettersMapCount = 1;
	    double m_letterWasInWord = 0.00;
	    double m_numberOfGames = 0.00;
	    int m_firstGuessToWonRoundConversionTracker = 0;

};

#endif // HANGMAN_HXX
