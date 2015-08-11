#include <iostream>

using namespace std;

template<int X, int Y>
struct Adder
{
   enum { result = X + Y };
   
   std::ostream & operator <<(std::ostream & os)
   {
   		return result;
   }
   
   static void print(std::ostream & os)
   {
   		os << "the answer inside of operator: " << result << "\n";
   }
};

typedef int (*MathFunc)(float, int);
 
int mul(float arg1, int arg2) {
    return arg2 * arg1;
}

int add(float arg1, int arg2) {
    return arg2 + arg1;
}

int div(float arg1, int arg2) {
    return arg2 / arg1;
}

int sub(float arg1, int arg2) {
    return arg2 - arg1;
}
 
int call_a_func(MathFunc call_this, int x, int y) {
    float output = call_this(x, y);
    return output;
}

int main()
{
	int a = 20, b = 3;
	// while(cin >> a >> b)

	// {
	int final_result = call_a_func(&mul, a, b);
	cout<< a << " * " << b << " = " << final_result << "\n";
	
    final_result = call_a_func(&add, a, b);
	cout<< a << " + " << b << " = " << final_result << "\n";
	
    final_result = call_a_func(&div, b, a);
	cout<< a << " / " << b << " = " << final_result << "\n";
	
    final_result = call_a_func(&sub, a, b);
	cout<< a << " - " << b << " = " << final_result << "\n";
	
	auto mult = [](int x, int y){return x * y;};
	auto mans = mult(a, b);
	cout << "Mult Using Lambda\n" << a << " * " << b << " = " << mans << "\nEnd of Lambda\n";
	
	auto divi = [](float x, float y){return x / y;};
	auto dans = divi(a, b);
	cout << "Div Using Lambda\n" << a << " / " << b << " = " << dans << "\nEnd of Lambda\n";

    cout << "Adder: 21 + 2 = " << Adder<21, 2>::result << "\n";

    Adder<19, 4>::print(cout);

	// }
	



}

