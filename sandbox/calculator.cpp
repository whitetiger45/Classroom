#include <iostream>
using namespace std;

int divide(int a, int b)
{
	asm(
		"xor %%edx, %%edx;"//xor sets the register to zero ="a" register to zero
		"div %%ebx;" //This divides the value in the dividend register(s) by "arg", see table below.
		: "=a"(a)
		: "a"(a), "b"(b)
		: "edx"
	);
	return a;
}

int multiply(int a, int b)
{
	asm(
		"xor %%edx, %%edx;"//xor sets the register to zero ="a" register to zero
		"mul %%ebx;" //This multiplies "arg" by the value of corresponding byte-length in the AX register.
		: "=a"(a)
		: "a"(a), "b"(b)
		: "edx"
	);
	return a;
}

int add(int a, int b)
{
	asm(
		"xor %%edx, %%edx;" //xor sets the register to zero ="a" register to zero
		"add %%ebx, %%eax;"//loads ebx into "a", "eax" into "b"
		: "=a"(a)
		: "a"(a), "b"(b)
		: "edx"
	);
	return a;
}

int subtract(int a, int b)
{
	asm(
		//"xor %%edx, %%edx;" //xor sets the register to zero ="a" register to zero
		"sub %%ebx, %%eax;"//loads ebx into 1, eax into 2
		: "=a"(a)
		: "a"(a), "b"(b)//ebx(1), eax(2)
		: "edx"
	);
	return a;
}

int main()
{
	int a, b;
	while (cin >> a >> b)
	{
		cout << a << " / " << b << " = " << divide(a, b) << endl;
		cout << a << " * " << b << " = " << multiply(a, b) << endl;
		cout << a << " + " << b << " = " << add(a, b) << endl;
		cout << a << " - " << b << " = " << subtract(a, b) << endl;
	}
	return 0;
}
