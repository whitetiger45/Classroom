#include <iostream>

struct foo {};

int main()
{
	std::cout << sizeof(void*) << std::endl;
	std::cout << sizeof(void (*)()) << std::endl;
	std::cout << sizeof(void (foo::*)()) << std::endl;
	return 0;
}