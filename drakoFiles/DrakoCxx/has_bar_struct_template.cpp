#include <iostream>
using namespace std;

template <typename C>
struct has_bar
{
public:
	typedef char yes_type;
	typedef short no_type;
	
	static no_type test(...);
	
	template <typename U = C>
	static yes_type test(int (*n)[sizeof(&U::bar)]);
	
	static bool const value = sizeof(test(nullptr)) == sizeof(yes_type);
};

struct a
{
	void bar()
	{
	}
};

struct b
{
	void foo()
	{
	}
};

int main()
{
	std::cout << "a has bar: " << has_bar<a>::value << std::endl;
	std::cout << "b has bar: " << has_bar<b>::value << std::endl;
	return 0;
}