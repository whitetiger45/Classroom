#include <iostream>
#include <sstream>
#include <string>

#include <cstdint>

bool is_netmask_valid(std::uint32_t mask)
{
	static std::uint32_t const msb = 1u << 31;
	
	if (mask == 0xFFFFFFFF || mask == 0)
		return false;
	
	while (mask & msb)
		mask <<= 1;
		
	return (mask == 0);
}

std::string ip2str(std::uint32_t ip)
{
	std::ostringstream builder;
	builder
		<< (ip >> 24) << "."
		<< ((ip >> 16) & 0xFF) << "."
		<< ((ip >> 8) & 0xFF) << "."
		<< (ip & 0xFF);
	return builder.str();
}

int main()
{
	std::uint32_t masks[] = { 0xFFFFFFF0, 0xFFFFFF00, 0xFFF0FF00, 0xF0FFF0F0 };
	std::string valid[] = { "invalid", "valid" };
	
	for (unsigned n = 0; n < (sizeof(masks) / sizeof(masks[0])); ++n)
		std::cout << ip2str(masks[n]) << " is " << valid[is_netmask_valid(masks[n])] << "\n";
	
	return 0;
}