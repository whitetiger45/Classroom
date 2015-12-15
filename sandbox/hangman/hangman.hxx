#ifndef HANGMAN_HXX
#define HANGMAN_HXX

#include <iostream>
#include <map>
#include <string>
#include <vector>

typedef std::vector<std::string> HangmanDictionary;
typedef	std::map<char,int> LetterTrackingMap;
typedef std::map<char,int>::iterator LetterTrackingMapIT;

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
			//std::cout << "RET: " << ret << "\n";
			return ret;
		}

		bool guessLetter(char value)
		{
			if(isupper(value))
				value = tolower(value);
			
			bool letterFound = false;
			for(int i = 0; i < m_wordLength; i++)
			{
				//std::cout<< "\nWord: " << m_incompleteWord << "\nm_word[" << i << "]: " << m_word[i] << "\n";
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

		void getMostFrequentLetterFromDictionaryWord()
		{
			    for(dictionaryWordLettersMapIT = dictionaryWordLettersMap.begin(); dictionaryWordLettersMapIT != dictionaryWordLettersMap.end(); dictionaryWordLettersMapIT++)
			    {
			        if(dictionaryWordLettersMapIT->second == dictionaryLettersMapmostFrequentCount)
			            std::cout << "\nMost frequent letter(s) to appear in the dictionary words this session: " << dictionaryWordLettersMapIT->first << "\n# of times it appeard: " << dictionaryWordLettersMapIT->second << "\n";
			    }
		}

	private:
		char m_word[256];
		char m_incompleteWord[256];
		char m_guessedLetters[26];
		int m_guessCount;
		int m_wordLength = 0;
		int m_roundsWon = 0;
		signed int m_triesLeft = 6;
		HangmanDictionary m_dictionary;

	    LetterTrackingMap dictionaryWordLettersMap;
	    LetterTrackingMapIT dictionaryWordLettersMapIT;
	    int dictionaryLettersMapmostFrequentCount = 1;

};

#endif // HANGMAN_HXX