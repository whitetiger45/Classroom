#include <array>
#include <cstdio>
#include <iostream>
#include <memory>
#include <regex>
#include <stdexcept>
#include <string>

using namespace std;

// https://stackoverflow.com/questions/478898/how-do-i-execute-a-command-and-get-the-output-of-the-command-within-c-using-po
string exec(const char* cmd) {
    array<char, 128> buffer;
    string result;
    unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

int main(int argc, char** argv){

    if(argc != 2){
        cout << "Usage: bin <base-10 integer to convert>\n";
        exit(0);
    }
    
    string userInputStr{argv[1]};
    regex userInputRegExp("^([\\d-.]+)$");
    smatch m;
    regex_match(userInputStr,m,userInputRegExp);

    if(!m.empty()){
        string cmd = "echo 'scale=32; obase=2; " + m.str(1) + "' | bc";
        cout << exec(const_cast<char*>(cmd.c_str()));
    }else cout << "Could not find an integer in input.\n";

    return 0;
}
