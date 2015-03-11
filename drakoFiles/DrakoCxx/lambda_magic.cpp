#include <iostream>
using namespace std;

int main()
{
	int n = 23;
	
	auto magic = [n]() mutable -> int {
		int result = n;
		n += n - 4;
		return result;
	};
	
	cout << magic() << endl;
	cout << magic() << endl;
	
	return 0;
}