#ifndef MATHQUIZ_HXX
#define MATHQUIZ_HXX

#include <ctime>
#include <iostream>
#include <string>

#define func(n, a) void show##n(){std::cout << a << "\n";}
func(Title, "\n* Math Quiz *")
#undef func

class Quizzer
{
    public:

            void setXAndY(unsigned int x, unsigned int y)
            {
                m_x = x;
                m_y = y;
                m_xStr = std::to_string(x);
                m_yStr = std::to_string(y);

                if(m_xStr.length() < 4)
                {
                    m_numberOfZerosToAddX = 4 - m_xStr.length();
                    for(int i = 0; i != m_numberOfZerosToAddX; i++)
                        m_zeroifyX += "0";
                    m_zeroifyX += m_xStr;
                    m_paddedXWithZeros = true;
                    // std::cout << "\nPadded x!\n";
                }

                if(m_yStr.length() < 4)
                {
                    m_numberOfZerosToAddY = 4 - m_yStr.length();
                    for(int i = 0; i != m_numberOfZerosToAddY; i++)
                        m_zeroifyY += "0";
                    m_zeroifyY += m_yStr;
                    m_paddedYWithZeros = true;
                    // std::cout << "\nPadded y!\n";
                }
            }

            unsigned int getX() const
            {
                return m_x;
            }

            unsigned int getY() const
            {
                return m_y;
            }

            std::string getXStr() const
            {
                return m_xStr;
            }

            std::string getYStr() const
            {
                return m_yStr;
            }

            std::string getPaddedXStr() const
            {
                return m_zeroifyX;
            }

            std::string getPaddedYStr() const
            {
                return m_zeroifyY;
            }

            void getProblem() const
            {
                if(m_paddedXWithZeros)
                    std::cout << "\nSolve: \n\t " << getYStr() << "\n      +  " << getPaddedXStr() << "\n\t______\n  User:  ";
                else if(m_paddedYWithZeros)
                    std::cout << "\nSolve: \n\t " << getXStr() << "\n      +  " << getPaddedYStr() << "\n\t______\n  User:  ";
                else 
                    std::cout << "\nSolve: \n\t " << getXStr() << "\n      +  " << getYStr() << "\n\t______\n  User:  ";
            }


    private:

        unsigned int m_x;
        unsigned int m_y;
        std::string m_xStr;
        std::string m_yStr;
        signed int m_numberOfZerosToAddX = 0;
        signed int m_numberOfZerosToAddY = 0;
        bool m_paddedXWithZeros = false;
        bool m_paddedYWithZeros = false;
        std::string m_zeroifyX;
        std::string m_zeroifyY;

};
#endif // MATHQUIZ_HXX