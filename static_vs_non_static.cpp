#include <iostream>
using namespace std;

struct foo
{
	int a;
	static int b;
};


int main() {
	foo f;
	f.a; // access a of object f
	foo * fp = new foo;
	fp->a; // access a of object pointed to by fp
	foo::b; // access b of class foo because it is static
	return 0;
}