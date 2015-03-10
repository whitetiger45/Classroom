#include <iostream>
using namespace std;

template<int X, int Y>
struct Adder
{
   enum { result = X + Y };
   
   std::ostream & operator <<(std::ostream & os)
   {
   	return os << result;
   }
   
//   	Adder<21, 2>::result;
   
};

int main() {
	//Adder<21, 2> a;
	auto a = Adder<21, 2>::result;
	std::cout<< Adder<21, 24>::result << endl;
	
	std::cout<< a << std::endl;
	
	return 0;
}