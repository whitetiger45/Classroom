/*
    A struct to help with splitting strings
    and removing punctuation marks.
*/

#include <cctype>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

using pr = pair<string,int>;
using HashMap = unordered_map<string,int>;

struct split{
    static string removePunc(string& s){
        string puncs = ";:,.?/\\][)(*&^\%$#@!";
        size_t pos = s.find_first_of(puncs);
        while(pos != string::npos){
            pos = s.find_first_of(puncs);
            if(pos == 0 && !s.substr(pos+1).empty())
                s = s.substr(pos+1);
            else if(s.substr(pos+1) != s.substr(0,pos) && !s.substr(pos+1).empty())
                s = s.substr(0,pos) + " " + s.substr(pos+1);
            else if(pos != 0 && s.substr(pos+1).empty())
                s = s.substr(0,pos);
        }
        return s;
    }

    static string lowercase(string& s){
        string uppers = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        size_t pos;
        while(pos != string::npos){
            pos = s.find_first_of(uppers);
            s[pos] = tolower(s[pos]);
        }
        return removePunc(s);
    }
    
    static void tokenize(HashMap& hm, string& x){
        size_t pos;
        while(pos != string::npos){
            pos = x.find(" ");
            string token = x.substr(0,pos);
            token = split::lowercase(token);
            x = x.substr(pos+1);
            if (token.length() > 0 && token.find(" ") == string::npos){
                auto it = hm.insert(pr(token,1));
                if(it.second == false) hm.at(token) += 1;
            }else if(token.length() > 0 && token.find(" ") != string::npos){
                tokenize(hm,token);
            }
        }
    }
};


int main() {
    string x = "This is a test. Can you split this string? What about this string here? It costs $9 total to build.";
    x += "Now the string is even longer.Random Can it handle issues with punctuation?Is the question. ";
    size_t pos;
    HashMap hm;
    split::tokenize(hm, x);
    
    for(auto& y : hm){
        cout << y.first << " - " << y.second << endl;
    }
    return 0;
}
