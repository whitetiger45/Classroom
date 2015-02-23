#include <iostream>
#include <string>
#include <regex>

using namespace std;

int main()
{
	std::string url("https://www.google.com/");
	std::regex parser("^([^:]+)://([^/]+)(.+)$");
	std::smatch match;
	
	string line = "Hello World.";
	// regex p2("([^]+).$"); //works "hello world" returned
	// regex p2("^[A-Za-z]+ ([A-Za-z]+)\\.");//works, "world" returned
	// regex p2("([A-Za-z].\\.*)");// works, "hello world." returned
	// regex p2("(^[A-Za-z]+) ([A-Za-z]+)\\.");// works, "[hello] [world]" returned
	regex p2("(.*)\\.");// works, "hello world." returned

	
	smatch m;
	
	if (std::regex_match(url, match, parser))
	{
		std::cout << "Protocol: " << match[1].str() << "\n";
		std::cout << "Host:     " << match[2].str() << "\n";
		std::cout << "Path:     " << match[3].str() << "\n";
	}
	int count = 1;
	auto c= std::regex_match(line, m, p2);
	// for(const auto & mat: line )
	// {
	if(std::regex_match(line, m, p2))
	{
		for (int i = 1; i < m.size(); ++i) 
		{
            std::ssub_match sub_match = m[i];
            std::string piece = sub_match.str();
            std::cout << "  submatch " << i << ": " << piece << '\n';
        }   
	}
	return 0;
}