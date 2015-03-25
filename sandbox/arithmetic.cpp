#include <iostream>
#include <bitset>


using namespace std;

template<int X, int Y>
struct Adder
{
	enum { result = X * Y };
 
	static void print(std::ostream & os)
	{
		os << "\nthe answer inside of operator: " << result << "\n";
	}
};

typedef float (*MathFunc)(float, float);
 
float divi(float arg1, float arg2) 
{
	return arg2 / arg1;
}

float multiply(float arg1, float arg2)
{
	return arg1 * arg2;
}

float call_a_func(MathFunc call_this)
{
	float x = 10.00;
	float y = 230.00;
	float output = call_this(x, y);
	return output;
}

float doMath(float x, float y)
{
	float output = (*multiply)(x, y);
	return output;
}

int main() 
{
 	
 	auto func = []() {cout << "\nHello World\n\n";};
	auto mult = [](int x, int y){return x * y;};

 	func();

	int x , y;
	x = y = 10;
	cout<< "Y: " << y << "\nX: " << bitset<32>(x);
	
	typedef Adder<14, 9> mul;
	mul::print(cout);
	
	float div_final_result = call_a_func(&divi);
	cout<< "div final result: " << div_final_result << "\n";

	float mult_final_result = doMath(1.5, 1.5);
	cout<< "mult final result: " << mult_final_result << "\n";

	auto mans = mult(10, 23);
	cout << "Mult Using Lambda\n" << 10 << " * " << 23 << " = " << mans << "\n";
	
	return 0;
}