#include <iostream>
using namespace std;

struct foo
{
	int const * bar(int const * const * const p) const
	{
		return *p;
	}
};

int main()
{
	int const n = 42;
	int const * const p = &n;
	int const * const * const pp = &p;
	
	foo const f;
	
	int const * (foo::* const b)(int const * const * const) const = &foo::bar;
	cout << *((f.*b)(pp)) << endl;
	
	return 0;
}