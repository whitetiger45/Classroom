#ifndef HANGMAN_HXX
#define HANGMAN_HXX

#include <iostream>
#include <map>
#include <string>
#include <vector>

class word
{
	public: 
		
		void setWord(std::string value)
		{
			m_word = value;
			for(int i = 0; i < m_word.size(); i++)
				m_incompleteWord += "_" ;
		}

		std::string showWord() const
		{
			return m_incompleteWord;
		}

		bool guessLetter(char value)
		{
			bool letterFound = false;
			for(int i = 0; i < m_word.size(); i++)
			{
				std::cout<< "\nWord: " << m_incompleteWord << "\nm_word[" << i << "]: " << m_word[i] << "\n";
				if(m_word[i] == value)
				{
					m_incompleteWord[i] = value;
					letterFound = true;
				}
			}
			m_triesLeft = (letterFound) ? m_triesLeft : m_triesLeft--;
			return letterFound;
		}

		std::string getGuessedLetters() const
		{
			return m_guessedLetters;
		}

		void addCharToGuessedLetters(char value)
		{
			m_guessedLetters += m_guessedLetters + ", "; 
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

		void printHangMan()
		{
			    switch(m_triesLeft)
			    {
			    	case 6:
    					    std::cout<< " ______\n";
							std::cout<< "|    |\n|    \n|     \n|           \n|______\n";
							m_triesLeft--;
							break;
			    	case 5:
    					    std::cout<< " ______\n";
							std::cout<< "|    |\n|    o\n|     \n|          \n|______\n";
							m_triesLeft--;
							break;
			    	case 4:
    					    std::cout<< " ______\n";
							std::cout<< "|    |\n|    o\n|    |\n|          \n|______\n";
							m_triesLeft--;
							break;
			    	case 3:
    					    std::cout<< " ______\n";
							std::cout<< "|    |\n|    o\n|   /|\n|          \n|______\n";
							m_triesLeft--;
							break;
			    	case 2:
    					    std::cout<< " ______\n";
							std::cout<< "|    |\n|    o\n|   /|\\ \n|        \n|______\n";
							m_triesLeft--;
							break;
			    	case 1:
    					    std::cout<< " ______\n";
							std::cout<< "|    |\n|    o\n|   /|\\\n|   /     \n|______\n";
							m_triesLeft--;
							break;
					case 0:
						    std::cout<< " ______\n";
    						std::cout<< "|    |\n|    o\n|   /|\\\n|   / \\  \n|______\n";
    						m_triesLeft--;
    						break;
					default:
						    std::cout<< " ______\n";
    						std::cout<< "|    |\n|    o\n|   /|\\\n|   / \\  \n|______\n";
			    }
		}

	private:
		std::string m_word;
		mutable std::string m_incompleteWord;
		std::string m_guessedLetters;
		signed int m_triesLeft = 6;
		std::vector<std::string> m_dictionary;

};

#endif // HANGMAN_HXX