#ifndef HANGMAN_HXX
#define HANGMAN_HXX

#include <chrono>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <regex>
#include <vector>

typedef bool tf;
typedef char l;
typedef double d;
typedef signed int si;
typedef struct tm * guessTime;
typedef std::map<l,si> LetterTrackingMap;
typedef std::map<l,si>::iterator LetterTrackingMapIT;
typedef std::vector<std::string> HangmanDictionary;

#define func(n, a) void show##n(){std::cout << a << "\n";}
func(Title, "\n\t   ***********\n\t   * Hangman *\n\t   ***********\n\t ______\n\t|     |\n\t|    \n\t|           o\n\t|          /|\\ \n\t|______    / \\\n\t*****************\n")
func(Menu, "\n\t Main Menu\n\t =========    \n     1: Survival Mode\n     2: Timed Mode\n     3: Regular Mode\n     4: High Scores\n     5: Quit\n")
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
sig_atomic_t userScoreTimedMode = 0;
sig_atomic_t userScoreRegularMode = 0;
sig_atomic_t totalGames = 0;

#define func(n, a, b, c) void declare##n(int param){std::cout << a ; ++b; ++c;}
func(UserWinsRoundRegularMode, "\n\t**********\n\t*You win!*\n\t**********\n\nThe correct word was: ", userScoreRegularMode, totalGames)
#undef func

#define func(n, a, b) void declare##n(int param){std::cout << a ; ++b;}
func(UserWinsRoundSurvivorMode, "\n\t**********\n\t*You win!*\n\t**********\n\nThe correct word was: ", userScoreSurvivorMode)
func(UserWinsRoundTimedMode, "\n\t**********\n\t*You win!*\n\t**********\n\nThe correct word was: ", userScoreTimedMode)
#undef func

#define func(n, a, b) void declare##n(int param){std::cout << a ; ++b;}
func(OutOfGuesses, "\nSorry, you are out of guesses...\n\nThe word was: ", totalGames)
#undef func

#define func(n, a, b, c) void declare##n(si param1, std::string param2){std::cout << a  << param1 << " seconds." << b <<  param2 << std::endl; ++c;}
func(OutOfTime, "\nYou took too long to answer...Game Over.\nTime to make last guess: ", "\n\nThe word was: ", totalGames)
#undef func

#define func(n, a, b) void score##n(){ std::cout << std::fixed << "\nWins | Total Games Played This Round  |     Win Percentage    \n  " << a << "  |            " << b << "                   |           " << std::setprecision(2) <<(d(d(a)/d(b)) * 100) << "\%      \n";}
func(BoardRegularMode, userScoreRegularMode, totalGames)
#undef func

#define func(n) void score##n(si modeScore, d gamesPlayed){ std::cout << std::fixed << "\nWins | Total Games Played This Round  |     Win Percentage    \n  " << modeScore << "  |            " << std::setprecision(0) << gamesPlayed << "                   |          " << std::setprecision(2) <<(d(d(modeScore)/d(gamesPlayed)) * 100) << "\%      \n";}
func(Board)
#undef func

#define func(n, a) void score##n(){ std::cout << std::fixed << "\nYou survived: " << a << " rounds\n";}
func(BoardSurvivorMode, userScoreSurvivorMode)
func(BoardTimedMode, userScoreTimedMode)
#undef func
//------------------------------------------------------------------------------------------------------------------------

auto lineWrapper = [](std::string lineToWrap, l c){for(si i = 0; i < lineToWrap.size(); i++)std::cout << c; std::cout << "\n";};

auto addWhiteSpaceAndEndlChar = 
[](std::string &appendStr, std::string wrapperString, si i)
	{
		while(appendStr.length() < wrapperString.length()-1)
		appendStr += " ";
		appendStr += "*";
		std::cout << appendStr << "\n";
	};

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
                m_dictionaryWordLettersMapIT = m_dictionaryWordLettersMap.begin();
                for(auto c: dictionaryWord)
                {
                    m_dictionaryWordLettersMapIT = m_dictionaryWordLettersMap.find(c);
                    if(m_dictionaryWordLettersMapIT != m_dictionaryWordLettersMap.end())
                    {
                        m_dictionaryWordLettersMapIT->second++;
                    }
                    else
                        m_dictionaryWordLettersMap[c] = 1;
                     
                    if(m_dictionaryWordLettersMapIT->second > dictionaryLettersMapmostFrequentCount)
                        dictionaryLettersMapmostFrequentCount = m_dictionaryWordLettersMapIT->second;
                }
        }
//-----------------------------------------------------------------------------------------------------------------------

        std::string getMostFrequentLetterFromDictionaryWord()
        {
            std::string ret;
           for(m_dictionaryWordLettersMapIT = m_dictionaryWordLettersMap.begin(); m_dictionaryWordLettersMapIT != m_dictionaryWordLettersMap.end(); m_dictionaryWordLettersMapIT++)
           {
               if(m_dictionaryWordLettersMapIT->second == dictionaryLettersMapmostFrequentCount)
               {
                   ret = "\nMost frequent letter(s) to appear in the dictionary words this session: ";
                   ret+= m_dictionaryWordLettersMapIT->first;
                   ret+= "\n# of times it appeard: " + std::to_string(m_dictionaryWordLettersMapIT->second) + "\n";
               }
           }
           return ret;
        }
//-----------------------------------------------------------------------------------------------------------------------

        void printMostFrequentLettersFromDictionaryWord()
        {
            for(m_dictionaryWordLettersMapIT = m_dictionaryWordLettersMap.begin(); m_dictionaryWordLettersMapIT != m_dictionaryWordLettersMap.end(); m_dictionaryWordLettersMapIT++)
            {
               if(m_dictionaryWordLettersMapIT->second == dictionaryLettersMapmostFrequentCount)
                   std::cout << "\nMost frequent letter(s) to appear in the dictionary words this session: " << m_dictionaryWordLettersMapIT->first << "\n# of times it appeard: " << m_dictionaryWordLettersMapIT->second << "\n";
            }
        }
//-----------------------------------------------------------------------------------------------------------------------

        si checkDictionaryMapLettersEqualToMaxCount()
        {
            si total = 0;
            for(m_dictionaryWordLettersMapIT = m_dictionaryWordLettersMap.begin(); m_dictionaryWordLettersMapIT != m_dictionaryWordLettersMap.end(); m_dictionaryWordLettersMapIT++)
                if(m_dictionaryWordLettersMapIT->second == dictionaryLettersMapmostFrequentCount)
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
            m_firstGuessLettersMapIT = m_firstGuessLettersMap.begin();
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

            m_firstGuessLettersMapIT = m_firstGuessLettersMap.find(value);

            if(m_firstGuessLettersMapIT != m_firstGuessLettersMap.end())
            {
                m_firstGuessLettersMapIT->second++;
            }
            else
                m_firstGuessLettersMap[value] = 1;
             
            if(m_firstGuessLettersMapIT->second > m_firstGuessLettersMapCount)
                m_firstGuessLettersMapCount = m_firstGuessLettersMapIT->second;
        }
//-----------------------------------------------------------------------------------------------------------------------

        void getFirstGuessAccuracy()
        {
            for(m_firstGuessLettersMapIT = m_firstGuessLettersMap.begin(); m_firstGuessLettersMapIT != m_firstGuessLettersMap.end(); m_firstGuessLettersMapIT++)
            {
                if(m_firstGuessLettersMapIT->second == m_firstGuessLettersMapCount)
                {
                    std::cout << "\nMost frequent letter(s) to be guessed first: " << m_firstGuessLettersMapIT->first << "\nNumber of times guessed first: "<< m_firstGuessLettersMapIT->second<<"\n";
                    std::cout << "\nFirst guess accuracy: " << std::setprecision(2) << (float)(m_letterWasInWord/m_numberOfGames) * 100 << "\% in " << std::setprecision(0) << m_numberOfGames << " game(s).\n";
                }
            }
        }
//-----------------------------------------------------------------------------------------------------------------------

        void resetFirstGuessLettersMap()
        {
  			m_firstGuessLettersMap.clear();
  			m_firstGuessLettersMapCount = 1;
            m_letterWasInWord = 0.00;
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

        void setRecordNumberOfGamesTimedMode(si newHighScore)
        {
            m_recordNumberOfGamesWonTimedMode = newHighScore;
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

        si getRecordNumberOfGamesWonTimedMode() const
        {
            return m_recordNumberOfGamesWonTimedMode;
        }
//-----------------------------------------------------------------------------------------------------------------------

        void resetSurvivorModeScore()
        {
            userScoreSurvivorMode = 0;
            m_numberOfGames = 0.00;
        }
//-----------------------------------------------------------------------------------------------------------------------

        void resetTimedModeScore()
        {
            userScoreTimedMode = 0;
            m_numberOfGames = 0.00;
        }
//-----------------------------------------------------------------------------------------------------------------------

        void resetRegularModeGames()
        {
            totalGames = 0;
            m_numberOfGames = 0.00;
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

        void setTimedMode()
        {
            m_timedModeEnabled = (m_timedModeEnabled) ? false : true;
        }
//-----------------------------------------------------------------------------------------------------------------------

        tf timedModeEnabled()
        {
            return m_timedModeEnabled;
        }
//-----------------------------------------------------------------------------------------------------------------------

        void setDisplayedRulesOnce()
        {
            m_displayedRulesOnce = (m_displayedRulesOnce) ? false : true;
        }
//-----------------------------------------------------------------------------------------------------------------------

        tf alreadyDisplayedRulesOnce()
        {
            return m_displayedRulesOnce;
        }
//-----------------------------------------------------------------------------------------------------------------------

        tf displayTimedModeRule()
        { 
            if(alreadyDisplayedRulesOnce())
            	return alreadyDisplayedRulesOnce();

	        std::cout << std::endl;
	        lineWrapper(std::string("\nAttention: In this mode, you must make your guess within 5 seconds or you will lose the round\n"), '*');
	        std::cout << "\nAttention:\n\nIn this mode, you must make your guess within 5 seconds or you will lose the round.";
	        std::cout << "\nThe timer will start once you see 'U: ', and it will stop once you have entered a letter.\n\n";
	        lineWrapper(std::string("\nAttention: In this mode, you must make your guess within 5 seconds or you will lose the round\n"), '*');
	        setDisplayedRulesOnce();

            return alreadyDisplayedRulesOnce();
        }
//-----------------------------------------------------------------------------------------------------------------------

        tf regularModeEnabled() const
        {
            return m_regularModeEnabled;
        }
//-----------------------------------------------------------------------------------------------------------------------

        void setRegularMode()
        {
            m_regularModeEnabled = (m_regularModeEnabled) ? false : true;
        }
//-----------------------------------------------------------------------------------------------------------------------

        si setUsersBestStreakOfAllTime(si allTimeHighScore)
        {
            m_maxStreakOfAllTime = allTimeHighScore;
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
            std::regex bestStreak("Best streak of all time: ([0-9]+)");
            std::regex mostGamesWonSurvivorMode("Record number of games won \\(Survivor\\): ([0-9]+)");
            std::regex mostGamesWonRegularMode("Record number of games won \\(Regular\\): ([0-9]+)");
            std::regex mostGamesWonRegularModeOld("Record number of games won: ([0-9]+)");
            std::regex mostGamesWonTimedMode("Record number of games won \\(Timed\\): ([0-9]+)");    
            std::cmatch cm;
            std::string::size_type maxStreak_str, recordNumberOfGamesSurvivorMode_str, recordNumberOfGamesRegular_str;
            std::string::size_type recordNumberOfGamesTimedMode_str;

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

                        //get record number of timed games won
                        if(std::regex_match ( line.c_str(), cm, mostGamesWonTimedMode ))
                        {
                            // std::cout << "** Games Debug Survivor: " << cm.str(1) << "\n";
                            std::string recordWinsTimedMode_str = cm.str(1);
                            setRecordNumberOfGamesTimedMode(std::stoi (recordWinsTimedMode_str , &recordNumberOfGamesTimedMode_str));
                            continue;
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
                    // resetSurvivorModeScore();
                }
                
                if(userScoreRegularMode > getRecordNumberOfGamesWonRegularMode())
                    setRecordNumberOfGamesRegularMode(userScoreRegularMode);

                if(userScoreTimedMode > getRecordNumberOfGamesWonTimedMode())
                {
                    setRecordNumberOfGamesTimedMode(userScoreTimedMode);
                    // resetTimedModeScore();
                }

                remove(fileName.c_str());
            }
            else if(userScoreSurvivorMode > getRecordNumberOfGamesWonSurvivorMode())
            {
                if(userScoreRegularMode > getRecordNumberOfGamesWonRegularMode())
                    setRecordNumberOfGamesRegularMode(userScoreRegularMode);

                if(userScoreTimedMode > getRecordNumberOfGamesWonTimedMode())
                {
                    setRecordNumberOfGamesTimedMode(userScoreTimedMode);
                    // resetTimedModeScore();
                }

                remove(fileName.c_str());
            }
            else if(userScoreRegularMode > getRecordNumberOfGamesWonRegularMode())
            {
                if(userScoreTimedMode > getRecordNumberOfGamesWonTimedMode())
                {
                    setRecordNumberOfGamesTimedMode(userScoreTimedMode);
                    // resetTimedModeScore();
                }
                remove(fileName.c_str());
            }
            else if(userScoreTimedMode > getRecordNumberOfGamesWonTimedMode())
            {
                remove(fileName.c_str());
            }
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

                if( userScoreTimedMode > getRecordNumberOfGamesWonTimedMode())
                    recordBook << "\nRecord number of games won (Timed): " << userScoreTimedMode << "\n";
                else recordBook << "\nRecord number of games won (Timed): " << getRecordNumberOfGamesWonTimedMode() << "\n\n\n";
            }
            using std::chrono::system_clock;
            system_clock::time_point today = system_clock::now();
            std::time_t tt;
            tt = system_clock::to_time_t ( today );
            recordBook << std::setw(80) << "Updated: " << ctime(&tt) << "\n";

            recordBook.close();

            setUserRecords();
        }
//-----------------------------------------------------------------------------------------------------------------------

        void showRecords()
        {
        	si i = getRecordNumberOfGamesWonSurvivorMode();
        	std::string sectionWrapper = "\nRecord number of games won: " + std::to_string(i) + "\n";
            std::cout << std::endl;
            lineWrapper(sectionWrapper, '*');
            // std::cout << "*\t High Scores\t     *\n";
            std::string title = "*        High Scores";
            addWhiteSpaceAndEndlChar(title, sectionWrapper, i);
            lineWrapper(sectionWrapper, '*');            // std::cout << "* Record number of games won *\n";
            std::string header1 = "* Record number of games won ";
            addWhiteSpaceAndEndlChar(header1, sectionWrapper, i);
            lineWrapper(sectionWrapper, '*');
            //std::cout << "Timed: " << getRecordNumberOfGamesWonTimedMode();
            // std::cout << "\nRegular: " << getRecordNumberOfGamesWonRegularMode();
            // std::cout << "\nSurvivor: " << getRecordNumberOfGamesWonSurvivorMode() << "\n";
            std::string tStr = "*        Timed: " + std::to_string(getRecordNumberOfGamesWonTimedMode());
            std::string rStr = "*        Regular: " + std::to_string(getRecordNumberOfGamesWonRegularMode());
            std::string sStr = "*        Survivor: " + std::to_string(getRecordNumberOfGamesWonSurvivorMode());
            std::string recordStreak = "*      Record streak: " + std::to_string(getUsersBestStreakOfAllTime());
	 		addWhiteSpaceAndEndlChar(tStr, sectionWrapper, i);
	 		addWhiteSpaceAndEndlChar(rStr, sectionWrapper, i);
	 		addWhiteSpaceAndEndlChar(sStr, sectionWrapper, i);
            lineWrapper(sectionWrapper, '*');            // std::cout << "* Record streak: " << getUsersBestStreakOfAllTime() << "*\n";
            addWhiteSpaceAndEndlChar(recordStreak, sectionWrapper, i);
            lineWrapper(sectionWrapper, '*');
        }
//-----------------------------------------------------------------------------------------------------------------------

        void startTimer()
        {
            time_t m_t = time(0);  
            m_userGuessClock = localtime( & m_t );
            m_clockMinuteBeforeGuess = m_userGuessClock->tm_min;
            m_clockSecondsBeforeGuess = m_userGuessClock->tm_sec;// get time now
        }
//-----------------------------------------------------------------------------------------------------------------------

        si getSecondsBeforeGuess() const
        {
            return m_clockSecondsBeforeGuess;
        }
//-----------------------------------------------------------------------------------------------------------------------

       	si getMinuteBeforeGuess() const
        {
            return m_clockMinuteBeforeGuess;
        }
//-----------------------------------------------------------------------------------------------------------------------

        void stopTimer()
        {
            time_t m_t = time(0);  
            m_userGuessClock = localtime( & m_t );
            m_clockMinuteAfterGuess = m_userGuessClock->tm_min;
            m_clockSecondsAfterGuess = m_userGuessClock->tm_sec;// get time now
        }
//-----------------------------------------------------------------------------------------------------------------------

        si getSecondsAfterGuess() const
        {
            return m_clockSecondsAfterGuess;
        }
//-----------------------------------------------------------------------------------------------------------------------

        si getMinuteAfterGuess() const
        {
            return m_clockMinuteAfterGuess;
        }
//-----------------------------------------------------------------------------------------------------------------------

        si getDifferenceBetweenGuessClocks() const
        {
            if((getMinuteAfterGuess() - getMinuteBeforeGuess()) == 0) 
            {
                return abs(getSecondsAfterGuess() - getSecondsBeforeGuess());
            }
            else
            {
            	si numberOfSecondsToMultiplySixtyBy = ( getMinuteAfterGuess() - getMinuteBeforeGuess() );
            	return abs( (( getSecondsAfterGuess() + ( numberOfSecondsToMultiplySixtyBy * 60 )) - getSecondsBeforeGuess() ) );
            }
        }
//-----------------------------------------------------------------------------------------------------------------------

        void setAverageTimeDifferenceToGuessTracker() 
        {
            m_averageTimeDifferenceBetweenGuesses += getDifferenceBetweenGuessClocks();
        }
//-----------------------------------------------------------------------------------------------------------------------

        void resetAverageTimeDifferenceToGuessTracker() 
        {
            m_averageTimeDifferenceBetweenGuesses = 0;
        }
//-----------------------------------------------------------------------------------------------------------------------

        si getAverageTimeDifferenceToGuessTracker() const
        {
            return m_averageTimeDifferenceBetweenGuesses;
        }
//-----------------------------------------------------------------------------------------------------------------------

       	d getAverageTimeToGuessTracker() const
        {
        	// std::cout << "\nMguess count: " << m_guessCount << "\n";
        	if(m_guessCount == 0 || getAverageTimeDifferenceToGuessTracker() == 0)
        		return getAverageTimeDifferenceToGuessTracker();
        	else
            	return ((d) getAverageTimeDifferenceToGuessTracker() / (d) (m_guessCount));
        }
//-----------------------------------------------------------------------------------------------------------------------

        tf userRespondedInTime() const
        {
            if(getDifferenceBetweenGuessClocks() > 5)
            {
                return false;
            }
            else
                return true;
        }
//-----------------------------------------------------------------------------------------------------------------------
      
        void getStats()
        {   
            updateRecordBook();
            
            std::cout << std::endl; 
            if(regularModeEnabled())
                scoreBoardRegularMode();
            else if(survivorModeEnabled())
            	scoreBoard(userScoreSurvivorMode, m_numberOfGames);
            else
            	scoreBoard(userScoreTimedMode, m_numberOfGames);

            lineWrapper(getMostFrequentLetterFromDictionaryWord(), '=');

            std::cout << "**Stats**\n";

            if(survivorModeEnabled())
                scoreBoardSurvivorMode();
            else if(timedModeEnabled())
                scoreBoardTimedMode();

            // std::cout << "\nRecord number of games won (Timed): " << getRecordNumberOfGamesWonTimedMode();
            // std::cout << "\nRecord number of games won (Regular): " << getRecordNumberOfGamesWonRegularMode();
            // std::cout << "\nRecord number of games won (Survivor): " << getRecordNumberOfGamesWonSurvivorMode() << "\n";

            if(checkDictionaryMapLettersEqualToMaxCount() == 1)
                std::cout << getMostFrequentLetterFromDictionaryWord();
            else
                printMostFrequentLettersFromDictionaryWord();

            getFirstGuessAccuracy();

            std::cout << "\n# of times first guess was correct and you won the round: ";
            std::cout << m_firstGuessToWonRoundConversionTracker << "\n";

            //testing 
            std::cout << "\nAverage time to make a guess: " << std::setprecision(1) << getAverageTimeToGuessTracker() << " seconds\n";

            updateRecordBook();

            std::cout << "\nBest streak: " << getMaxStreak() << "\n";
            lineWrapper(getMostFrequentLetterFromDictionaryWord(), '=');
        }

//-----------------------------------------------------------------------------------------------------------------------

  private:

        tf m_survivorModeEnabled = false;
        tf m_timedModeEnabled = false;
        tf m_regularModeEnabled = false;
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
        si m_recordNumberOfGamesWonTimedMode = 0;
        si m_triesLeft = 6;
        HangmanDictionary m_dictionary;

        LetterTrackingMap m_dictionaryWordLettersMap;
        LetterTrackingMapIT m_dictionaryWordLettersMapIT;
        si dictionaryLettersMapmostFrequentCount = 1;

        LetterTrackingMap m_firstGuessLettersMap;
        LetterTrackingMapIT m_firstGuessLettersMapIT;
        tf m_firstGuessWasCorrect = false;
        si m_firstGuessLettersMapCount = 1;
        d m_letterWasInWord = 0.00;
        d m_numberOfGames = 0.00;
        si m_firstGuessToWonRoundConversionTracker = 0;

        //average time per guessed letter tracker stuff
        guessTime m_userGuessClock;
        si m_clockSecondsBeforeGuess = 0;
        si m_clockSecondsAfterGuess = 0;
        si m_clockMinuteBeforeGuess = 0;
        si m_clockMinuteAfterGuess = 0;
        si m_averageTimeDifferenceBetweenGuesses = 0;

        //timed play stuff
        tf m_displayedRulesOnce;
};

#endif // HANGMAN_HXX
