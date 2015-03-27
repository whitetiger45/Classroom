#include <iostream>
#include <bitset>
#include <algorithm>
#include <vector>


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

float subtract(float arg1, float arg2)
{
	return arg1 - arg2;
}

float multiply(float arg1, float arg2)
{
	return arg1 * arg2;
}

float add(MathFunc f, float x, float y)
{
	return x + y;
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

float arithmetic(MathFunc f, float x, float y)
// float doMath2(float(*f)(float, float), float x, float y)
{
	float output = (*f)(x, y);
	return output;
}

void myfunction (int i) 
{  // function:
  std::cout << ' ' << i;
}

struct myclass {           // function object type:
  void operator() (int i) {std::cout << ' ' << i;}
} myobject;

int main() 
{
 	
 	auto func = []() {cout << "Hello World\n\n";};
	auto mult = [](int x, int y){return x * y;};
	auto divide = [](float x, float y){return x / y;};

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

	float subtract_final_result = arithmetic(&subtract, 1.9, 1.5);
	cout<< "subtract final result: " << subtract_final_result << "\n";

	auto mans = mult(10, 23);
	cout << "Mult Using Lambda\n" << 10 << " * " << 23 << " = " << mans << "\n";

	auto dans = divide(23, 11);
	cout << "Divide Answer: " << dans << "\n" ;

	vector<int> n;

	for(int i = 0; i < 11; i++)
	{
		n.push_back(i);
	}

	for(int x : n)
		cout<< "5 * " << x << " = " << mult(5, x) << "\n";

	auto l = [](int num){return num * 2;};
	cout << "myvector contains:";
  	for_each (n.begin(), n.end(), [](int num){cout<< " " << num * 2;});
  	cout << '\n';
	
	return 0;
}
