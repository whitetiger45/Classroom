#include <iostream>
#include <sstream>
#include <string>

#include <cstdint>

using namespace std;

string ip2str(uint32_t ip)
{
	ostringstream builder;
	builder
		<< (ip >> 24) << "."
		<< ((ip >> 16) & 0xFF) << "."
		<< ((ip >> 8) & 0xFF) << "."
		<< (ip & 0xFF);
	return builder.str();
}

int main()
{
	uint32_t ip   = 0xBADC0FFE;
	uint32_t mask = 0xFFFFF000;
	
	cout << "IP:        " << ip2str(ip) << "\n";
	cout << "Netmask:   " << ip2str(mask) << "\n";
	cout << "Subnet:    " << ip2str(ip & mask) << "\n";
	cout << "Broadcast: " << ip2str((ip & mask) | (~mask)) << "\n";
	
	return 0;
}