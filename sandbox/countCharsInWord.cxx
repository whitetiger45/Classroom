#include <iostream>
#include <map>
#include <algorithm>
#include <string>

using namespace std;

int main() 
{
    map<char,int> m;
    map<char,int>::iterator it;
    it = m.begin();
    std::string word;
    int max = 1;
    char userWord[256];
    cout << "Enter a word: ";
    cin.getline(userWord, 256);

    for(auto c: std::string(userWord))
    {
        it = m.find(c);
        if(it != m.end())
        {
            it->second++;
        }
        else
            m[c] = 1;
         
        if(it->second > max)
            max = it->second;
    }
    for(auto it = m.begin(); it != m.end(); it++)
    {
        if(it->second == max)
            cout <<"Most common letter: " << it->first << "\n# of occurences: " << it->second << "\n";
    }

return 0;
}