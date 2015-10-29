// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

int main () {
  string line;
  ifstream myfile ("presidents.txt");
  std::smatch sm;
  int i = 0;
  std::regex presLine("^([0-9]+). ([A-Za-z]+ ?[A-Z]*\.* [A-Za-z]+ ?[A-Za-z]*) .*.*.*((Democratic-Republican|Democrat|Republican|Whig|Federalist|Union)).*.*");
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      std::regex_match (line,sm,presLine);
      if(i++ == 0)
        continue;
      std::cout << sm[1]<< ") Name: " << sm[2] << ", Party: " << sm[3] << "\n";
    }
    myfile.close();
  }

  else cout << "Unable to open file"; 

  return 0;
}