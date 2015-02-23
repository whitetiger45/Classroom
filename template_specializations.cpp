#include <iostream>

template <typename T>
void print(T const & t)
{
	std::cout << "unknown type: " << t << std::endl;
}

template <>
void print<int>(int const & i)
{
	std::cout << "int: " << i << std::endl;
}

template <>
void print<double>(double const & d)
{
	std::cout << "double: " << d << std::endl;
}

int main()
{
	print("Hello world!");
	print(42);
	print(3.14159);
	return 0;
}