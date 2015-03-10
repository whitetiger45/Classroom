#include <iostream>

int main()
{
	// xx.xx.xx.xx/24, assume we already parsed the 24 out of there
	int slash_notated = 24;
	// Bryan: you can also modify the number above to see how it changes the result
	
	// this way we can calculate the actual netmask
	unsigned mask = ~((1 << (32 - slash_notated)) - 1);
	// or better
	unsigned mask2 = (0xFFFFFFFF << (32 - slash_notated)) /* & 0xFFFFFFFF */;
	// we can optimize the "& 0xFFFFFFFF" away in the end
	
	// this way we can print it out or turn it into a string or whatever
	unsigned char * parts = (unsigned char *)(&mask);
	std::cout
		<< (int)(parts[3]) << "."
		<< (int)(parts[2]) << "."
		<< (int)(parts[1]) << "."
		<< (int)(parts[0]) << "\n";
	
	// or (this one might be faster and is also actually more portable)
	std::cout
		<< (mask2 >> 24) << "."
		<< ((mask2 >> 16) & 0xFF) << "."
		<< ((mask2 >> 8) & 0xFF) << "."
		<< (mask2 & 0xFF) << std::endl;
	
	return 0;
}