#include <iostream>
#include <string>
#include <memory>
#include <typeinfo>
#include <functional>

#include <cstdlib>

#include <cxxabi.h>

template <typename T>
std::string typestr()
{
	char const * name = typeid(T).name();
	int status;
	std::unique_ptr<char, void (*)(void *)> res {
		abi::__cxa_demangle(name, nullptr, nullptr, &status),
		std::free
	};
	return (status == 0 ? res.get() : name);
}

template <typename Functor>
struct functor_traits
	: functor_traits<decltype(&Functor::operator())>
{
};

template <typename Result, typename... Args>
struct functor_traits<Result (*)(Args...)>
{
	typedef Result result;
};

template <typename Result, typename Class, typename... Args>
struct functor_traits<Result (Class::*)(Args...)>
{
	typedef Result result;
};

template <typename Result, typename Class, typename... Args>
struct functor_traits<Result (Class::*)(Args...) const>
{
	typedef Result result;
};

#define RESULT(functor) typestr<typename functor_traits<decltype(functor)>::result>()

int main()
{
	// simple function
	std::cout << "Result of main: " << RESULT(&main) << std::endl;
	
	// method
	std::cout << "Result of std::string::substr: " << RESULT(&std::string::substr) << std::endl;
	
	// functor
	std::cout << "Result of std::less::operator(): " << RESULT(std::less<float>()) << std::endl;
	
	// lambda
	auto answer = [](){ return 42; };
	std::cout << "Result of [](){ return 42; }: " << RESULT(answer) << std::endl;
	return 0;
}