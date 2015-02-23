#include <iostream>

using namespace std;

typedef int (*MathFunc)(float, int);
 
int do_math(float arg1, int arg2) {
    return arg2 * arg1;
}
 
int call_a_func(MathFunc call_this) {
	float x = 9.00;
	float y = 10.00;
    float output = call_this(x, y);
    return output;
}

int main()
{
	int final_result = call_a_func(&do_math);
	cout<< final_result << endl;
}

