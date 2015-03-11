#include <iostream>
using namespace std;

struct foo
{
	int n;
};

typedef void (*codeptr)();
struct gnu_member_function_pointer
{
	union
	{
		codeptr funcaddr;
		int vtable_index;
	};
	int delta;
};

void print(foo * _this)
{
	cout << _this->n << endl;
}

int main()
{
	foo f;
	f.n = 42;
	
	gnu_member_function_pointer mfp = { 0 };
	mfp.funcaddr = reinterpret_cast<codeptr>(&print);
	
	typedef void (foo::*meth_ptr)();
	union
	{
		gnu_member_function_pointer gmfp;
		meth_ptr mp;
	} caster;
	
	caster.gmfp = mfp;
	meth_ptr out = caster.mp;
	
	(f.*out)();
	
	return 0;
}