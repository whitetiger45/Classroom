#include <iostream>

class object {};

class foo : public object
{
public:
	void set_value(int val) { value = val; }
private:
	int value;
};

class bar : public object
{
public:
	void show() { std::cout << value << std::endl; }
private:
	int value;
};

int main()
{
	foo f;
	
	object * obj = &f;
	((foo*)obj)->set_value(42);
	((bar*)obj)->show();
	return 0;
}