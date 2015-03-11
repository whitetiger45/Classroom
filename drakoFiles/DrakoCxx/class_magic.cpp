#include <iostream>
using namespace std;

int main()
{
	int n = 23;
	
	class anon_1 {
	private:
		int n;
		
	public:
		anon_1(int n)
		: n(n)
		{
		}
		
		int operator () ()
		{
			int result = n;
			n += n - 4;
			return result;
		}
	} magic(n);
	
	cout << magic() << endl;
	cout << magic() << endl;
	
	return 0;
}