#ifndef HANGMAN_HXX
#define HANGMAN_HXX

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <regex>
#include <vector>

typedef bool tf;
typedef char l;
typedef double d;
typedef signed int si;
typedef	std::map<l,si> LetterTrackingMap;
typedef std::map<l,si>::iterator LetterTrackingMapIT;
typedef std::vector<std::string> HangmanDictionary;

#define func(n, a) void show##n(){std::cout << a << "\n";}
func(Title, "\n\t   ***********\n\t   * Hangman *\n\t   ***********\n\t ______\n\t|     |\n\t|    \n\t|           o\n\t|          /|\\ \n\t|______    / \\\n\t*****************\n")
func(Menu, "\n\t Main Menu\n\t =========    \n     1: Survival Mode\n     2: Regular Mode\n     3: Quit\n")
func(SubMenu, "\nWhat would you like to do?\n_______________________________\n\n1) Guess Letter\n2) Guess Word\n3) See what letters you've guessed\n4) Show Unfinished Word\n5) How Many Incorrect Guesses Left?\n6) Display HangMan Board\n7) Exit App\n_______________________________\n")
#undef func

#define func(n,a) void ask##n(){std::cout << a << "\n";}
func(ForLetter, "\nWhat letter would you like to guess?\n(Enter 1 to go back to main menu)")
func(PlayAgain, "\n(Type 's' to see your current stats and 'm' to return to mode selection menu)\nPlay again? [n/y/s/m]: ")
func(ForSuspectedWord, "What do you think the word is?")
#undef func

//------------------------------------------------------------------------------------------------------------------------
//scoreboard stuff
sig_atomic_t userScoreSurvivorMode = 0;
sig_atomic_t userScoreRegularMode = 0;
sig_atomic_t totalGames = 0;

#define func(n, a, b, c) void declare##n(int param){std::cout << a ; ++b; ++c;}
func(UserWinsRoundSurvivorMode, "\n\t**********\n\t*You win!*\n\t**********\n\nThe correct word was: ", userScoreSurvivorMode, totalGames)
func(UserWinsRoundRegularMode, "\n\t**********\n\t*You win!*\n\t**********\n\nThe correct word was: ", userScoreRegularMode, totalGames)
#undef func

#define func(n, a, b) void declare##n(int param){std::cout << a ; ++b;}
func(OutOfGuesses, "\nSorry, you are out of guesses...\nThe correct word was: ", totalGames)
#undef func


#define func(n, a, b) void score##n(){ std::cout << std::fixed << "\nWins | Total Games Played This Round  |     Win Percentage    \n  " << a << "  |            " << b << "                   |           " << std::setprecision(2) <<(d(d(a)/d(b)) * 100) << "\%      \n";}
func(BoardSurvivorMode, userScoreSurvivorMode, totalGames)
func(BoardRegularMode, userScoreRegularMode, totalGames)
//------------------------------------------------------------------------------------------------------------------------

auto lineWrapper = [](std::string lineToWrap, l c){for(si i = 0; i < lineToWrap.size(); i++)std::cout << c; std::cout << "\n";};

class word
{
	public: 
//-----------------------------------------------------------------------------------------------------------------------

		void setWord(std::string value)
		{
			m_guessCount = 0;
			m_guessedLetters[0] = '\0';
	  		std::size_t length = value.copy(m_word, value.length(), 0);
  			m_word[length]='\0';
  			m_wordLength = value.length();
			for(si i = 0; i < value.length(); i++)
				m_incompleteWord[i] = '_' ;

			m_incompleteWord[length] = '\0';

	        trackDictionaryLetters(value);
	        m_numberOfGames++;
		}
//-----------------------------------------------------------------------------------------------------------------------

		const l* showWord() const
		{
			return m_incompleteWord;
		}
//-----------------------------------------------------------------------------------------------------------------------

		std::string incompleteWord() const
		{
			std::string ret;
			for(auto c : std::string(m_incompleteWord))
			{
				ret = ret + " " + c;
			}
			return ret;
		}
//-----------------------------------------------------------------------------------------------------------------------

		tf guessLetter(l value)
		{
			if(isupper(value))
				value = tolower(value);

			if( getGuessedLetters() == "" )
			{
				trackFirstGuessAccuracy(value);
			}

			tf letterFound = false;

			for(si i = 0; i < m_wordLength; i++)
			{
				if(m_word[i] == value)
				{
					m_incompleteWord[i] = value;
					letterFound = true;
				}
			}

			for(si i = 0; i < m_guessCount; i++)
				if(m_guessedLetters[i] == value)
				{
					std::cout << "\nYou already guessed that letter!\n";
					return true;
				}

			m_triesLeft = (letterFound) ? m_triesLeft : m_triesLeft--;
			addlToGuessedLetters(value);

			return letterFound;
		}
//-----------------------------------------------------------------------------------------------------------------------

		std::string getGuessedLetters() const
		{
			return m_guessedLetters;
		}
//-----------------------------------------------------------------------------------------------------------------------

		void addlToGuessedLetters(l value)
		{
			m_guessedLetters[m_guessCount++] = value;
			m_guessedLetters[m_guessCount] = '\0'; 
		}
//-----------------------------------------------------------------------------------------------------------------------

		std::string getWord() const
		{
			return m_word;
		}
//-----------------------------------------------------------------------------------------------------------------------

		si getTriesLeft() const
		{
			return m_triesLeft;
		}
//-----------------------------------------------------------------------------------------------------------------------

		void subtractTry()
		{
			m_triesLeft--;
		}
//-----------------------------------------------------------------------------------------------------------------------

		void resetTries()
		{
			m_triesLeft = 6;
			for(auto x : m_guessedLetters)
				x = ' ';
		}
//-----------------------------------------------------------------------------------------------------------------------

		void displayHangMan()
		{
			    switch(m_triesLeft)
			    {
			    	case 6:
    					    std::cout<< " ______\n";
							std::cout<< "|     |\n|    \n|     \n|           \n|______\n";
							break;
			    	case 5:
    					    std::cout<< " ______\n";
							std::cout<< "|     |\n|     o\n|     \n|          \n|______\n";
							break;
			    	case 4:
    					    std::cout<< " ______\n";
							std::cout<< "|     |\n|     o\n|     |\n|          \n|______\n";
							break;
			    	case 3:
    					    std::cout<< " ______\n";
							std::cout<< "|     |\n|     o\n|    /|\n|          \n|______\n";
							break;
			    	case 2:
    					    std::cout<< " ______\n";
							std::cout<< "|     |\n|     o\n|    /|\\ \n|        \n|______\n";
							break;
			    	case 1:
    					    std::cout<< " ______\n";
							std::cout<< "|     |\n|     o\n|    /|\\\n|    /     \n|______\n";
							break;
					case 0:
						    std::cout<< " ______\n";
    						std::cout<< "|     |\n|     o\n|    /|\\\n|    / \\  \n|______\n";
    						break;
					default:
						    std::cout<< " ______\n";
    						std::cout<< "|     |\n|     o\n|    /|\\\n|    / \\  \n|______\n";
			    }
		}
//-----------------------------------------------------------------------------------------------------------------------

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
//-----------------------------------------------------------------------------------------------------------------------

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
//-----------------------------------------------------------------------------------------------------------------------

		void printMostFrequentLettersFromDictionaryWord()
		{
		    for(dictionaryWordLettersMapIT = dictionaryWordLettersMap.begin(); dictionaryWordLettersMapIT != dictionaryWordLettersMap.end(); dictionaryWordLettersMapIT++)
		    {
		       if(dictionaryWordLettersMapIT->second == dictionaryLettersMapmostFrequentCount)
		           std::cout << "\nMost frequent letter(s) to appear in the dictionary words this session: " << dictionaryWordLettersMapIT->first << "\n# of times it appeard: " << dictionaryWordLettersMapIT->second << "\n";
		    }
		}
//-----------------------------------------------------------------------------------------------------------------------

		si checkDictionaryMapLettersEqualToMaxCount()
		{
			si total = 0;
			for(dictionaryWordLettersMapIT = dictionaryWordLettersMap.begin(); dictionaryWordLettersMapIT != dictionaryWordLettersMap.end(); dictionaryWordLettersMapIT++)
				if(dictionaryWordLettersMapIT->second == dictionaryLettersMapmostFrequentCount)
					total++;
			return total;
		}
//-----------------------------------------------------------------------------------------------------------------------

		void setFirstGuessWasCorrectValue()
		{
			m_firstGuessWasCorrect = true;
		}
//-----------------------------------------------------------------------------------------------------------------------

		void trackFirstGuessAccuracy(l value)
		{
			std::map<si, std::string> firstGuessMessageMap;

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
//-----------------------------------------------------------------------------------------------------------------------

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
//-----------------------------------------------------------------------------------------------------------------------

		void setMaxStreak(si currentStreak)
		{
			m_streak = currentStreak;
		}
//-----------------------------------------------------------------------------------------------------------------------

		si getMaxStreak()
		{
			return m_streak;
		}
//-----------------------------------------------------------------------------------------------------------------------

		tf checkIfFirstGuessWasCorrect() const
		{
			return m_firstGuessWasCorrect;
		}
//-----------------------------------------------------------------------------------------------------------------------

		void resetFirstGuessWasCorrectValue()
		{
			m_firstGuessWasCorrect = false;
		}
//-----------------------------------------------------------------------------------------------------------------------

		void incrementFirstGuessToWonRoundConversionTracker()
		{
			m_firstGuessToWonRoundConversionTracker++;
		}
//-----------------------------------------------------------------------------------------------------------------------

		void setRecordNumberOfGamesSurvivorMode(si newHighScore)
		{
			m_recordNumberOfGamesWonSurvivorMode = newHighScore;
		}
//-----------------------------------------------------------------------------------------------------------------------

		void setRecordNumberOfGamesRegularMode(si newHighScore)
		{
			m_recordNumberOfGamesWonRegularMode = newHighScore;
		}
//-----------------------------------------------------------------------------------------------------------------------

		si getRecordNumberOfGamesWonSurvivorMode() const
		{
			return m_recordNumberOfGamesWonSurvivorMode;
		}
//-----------------------------------------------------------------------------------------------------------------------

		si getRecordNumberOfGamesWonRegularMode() const
		{
			return m_recordNumberOfGamesWonRegularMode;
		}
//-----------------------------------------------------------------------------------------------------------------------

		void resetSurvivorModeScore()
		{
			userScoreSurvivorMode = 0;
		}
//-----------------------------------------------------------------------------------------------------------------------

		void setSurvivorMode()
		{
			m_survivorModeEnabled = (m_survivorModeEnabled) ? false : true;
		}
//-----------------------------------------------------------------------------------------------------------------------

		tf survivorModeEnabled()
		{
			return m_survivorModeEnabled;
		}

//-----------------------------------------------------------------------------------------------------------------------

		si getUsersBestStreakOfAllTime() const
		{
			return m_maxStreakOfAllTime;
		}
//-----------------------------------------------------------------------------------------------------------------------

		void setUserRecords()
		{
			std::ifstream recordBook("hangManRecordBook.txt");
			std::string line;
            std::regex bestStreak("Best streak of all time: ([0-9])");
            std::regex mostGamesWonSurvivorMode("Record number of games won \\(Survivor\\): ([0-9])");
            std::regex mostGamesWonRegularMode("Record number of games won \\(Regular\\): ([0-9])");
            std::regex mostGamesWonRegularModeOld("Record number of games won: ([0-9])");
            std::cmatch cm;
            std::string::size_type maxStreak_str, recordNumberOfGamesSurvivorMode_str, recordNumberOfGamesRegular_str;
			if(recordBook.is_open())
			{
                try 
                {
	            	while(getline(recordBook,line))
	            	{
	            		if(line == "")
	            			continue;

		        	 	if(std::regex_match ( line.c_str(), cm, bestStreak ))
		        	 	{
			        	 	std::string recordStreak_str = cm.str(1);
							m_maxStreakOfAllTime = std::stoi (recordStreak_str, &maxStreak_str);
							continue;
						}
						// std::cout << "Line: " << line << "\n";
						//get record number of games won survivor mode
		        	 	if(std::regex_match ( line.c_str(), cm, mostGamesWonSurvivorMode ))
		        	 	{
		        	 		// std::cout << "** Games Debug Survivor: " << cm.str(1) << "\n";
		        	 		std::string recordWinsSurvivorMode_str = cm.str(1);
		        	 		setRecordNumberOfGamesSurvivorMode(std::stoi (recordWinsSurvivorMode_str , &recordNumberOfGamesSurvivorMode_str));
		        	 		continue;
		        	 	}

		        	 	//get record number of regular games won
		        	 	if(std::regex_match ( line.c_str(), cm, mostGamesWonRegularMode ))
		        	 	{
		        	 		// std::cout << "** Games Debug Regular: " << cm.str(0) << " **\n";
		        	 		std::string recordWinsRegularMode_str = cm.str(1);
		        	 		setRecordNumberOfGamesRegularMode(std::stoi (recordWinsRegularMode_str , &recordNumberOfGamesRegular_str));
		        	 	}
		        	 	else if(std::regex_match ( line.c_str(), cm, mostGamesWonRegularModeOld ))
		        	 	{
		        	 		std::string recordWinsRegularMode_str = cm.str(1);
		        	 		setRecordNumberOfGamesRegularMode(std::stoi (recordWinsRegularMode_str , &recordNumberOfGamesRegular_str));
		        	 	}
	        	 	}
	        	 }catch(const std::invalid_argument& ia){}
        	}
            recordBook.close();
		}
//-----------------------------------------------------------------------------------------------------------------------

		void updateRecordBook()
		{
			std::string fileName("hangManRecordBook.txt");
            setUserRecords();

			if(getMaxStreak() > getUsersBestStreakOfAllTime())
			{
				if(userScoreSurvivorMode > getRecordNumberOfGamesWonSurvivorMode())
				{
					setRecordNumberOfGamesSurvivorMode(userScoreSurvivorMode);
					resetSurvivorModeScore();
				}
				
				if(userScoreRegularMode > getRecordNumberOfGamesWonRegularMode())
					setRecordNumberOfGamesRegularMode(userScoreRegularMode);

                remove(fileName.c_str());
			}
            else if(userScoreSurvivorMode > getRecordNumberOfGamesWonSurvivorMode())
            {
				if(userScoreRegularMode > getRecordNumberOfGamesWonRegularMode())
					setRecordNumberOfGamesRegularMode(userScoreRegularMode);

            	remove(fileName.c_str());
            }
        	else if(userScoreRegularMode > getRecordNumberOfGamesWonRegularMode())
            	remove(fileName.c_str());
    		else return;

            std::ofstream recordBook(fileName);
            if(recordBook.is_open())
            {
            	if( getMaxStreak() > getUsersBestStreakOfAllTime() )
            		recordBook << "Best streak of all time: " << getMaxStreak() << "\n";
            	else recordBook << "Best streak of all time: " << getUsersBestStreakOfAllTime() << "\n";

            	if( userScoreSurvivorMode > getRecordNumberOfGamesWonSurvivorMode())
            		recordBook << "\nRecord number of games won (Survivor): " << userScoreSurvivorMode << "\n";
            	else recordBook << "\nRecord number of games won (Survivor): " << getRecordNumberOfGamesWonSurvivorMode() << "\n";

            	if( userScoreRegularMode > getRecordNumberOfGamesWonRegularMode())
            		recordBook << "\nRecord number of games won (Regular): " << userScoreRegularMode << "\n";
            	else recordBook << "\nRecord number of games won (Regular): " << getRecordNumberOfGamesWonRegularMode() << "\n";
            }

            recordBook.close();

            setUserRecords();
		}
//-----------------------------------------------------------------------------------------------------------------------
		
		void getStats()
		{	
			updateRecordBook();
			
			std::cout << std::endl; 
			if(survivorModeEnabled()) 
				scoreBoardSurvivorMode();
			else
				scoreBoardRegularMode();

			std::cout << std::endl;	

		    lineWrapper(getMostFrequentLetterFromDictionaryWord(), '=');

		    std::cout << "**Stats**\n";

		    std::cout << "\nRecord number of games won (Survivor): " << getRecordNumberOfGamesWonSurvivorMode();
		    std::cout << " | Record number of games won (Regular): " << getRecordNumberOfGamesWonRegularMode() << "\n";

		    if(checkDictionaryMapLettersEqualToMaxCount() == 1)
		        std::cout << getMostFrequentLetterFromDictionaryWord();
		    else
		        printMostFrequentLettersFromDictionaryWord();

		    getFirstGuessAccuracy();

		    std::cout << "# of times first guess was correct and user won the round: ";
		    std::cout << m_firstGuessToWonRoundConversionTracker << "\n";

		    updateRecordBook();

		    std::cout << "\nCurrent best streak: " << getMaxStreak();
		    std::cout << " | Record streak of all time: " << getUsersBestStreakOfAllTime() << "\n";

		    lineWrapper(getMostFrequentLetterFromDictionaryWord(), '=');
		}
//-----------------------------------------------------------------------------------------------------------------------

	private:

		tf m_survivorModeEnabled = false;
		l m_word[256];
		l m_incompleteWord[256];
		l m_guessedLetters[26];
		si m_guessCount;
		si m_wordLength = 0;
		si m_roundsWon = 0;
		si m_streak = 0;
		si m_maxStreakOfAllTime = 0;
		si m_recordNumberOfGamesWonSurvivorMode = 0;
		si m_recordNumberOfGamesWonRegularMode = 0;
		si m_triesLeft = 6;
		HangmanDictionary m_dictionary;

	    LetterTrackingMap dictionaryWordLettersMap;
	    LetterTrackingMapIT dictionaryWordLettersMapIT;
	    si dictionaryLettersMapmostFrequentCount = 1;

	    LetterTrackingMap m_firstGuessLettersMap;
	    LetterTrackingMapIT m_m_firstGuessLettersMapIT;
	    tf m_firstGuessWasCorrect = false;
	    si m_m_firstGuessLettersMapCount = 1;
	    d m_letterWasInWord = 0.00;
	    d m_numberOfGames = 0.00;
	    si m_firstGuessToWonRoundConversionTracker = 0;

};

#endif // HANGMAN_HXX
