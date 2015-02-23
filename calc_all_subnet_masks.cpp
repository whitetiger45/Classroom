#include <iostream>
using namespace std;

int main()
{
	unsigned int mask = 0xFFFFFFFF;
	while (mask)
	{
		std::cout
			<< (mask >> 24) << "."
			<< ((mask >> 16) & 0xFF) << "."
			<< ((mask >> 8) & 0xFF) << "."
			<< (mask & 0xFF) << "\n";
		mask <<= 1;
	}
	
	return 0;
}