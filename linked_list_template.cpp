#include <iostream>

template <int Value, typename Next>
struct Node;

struct EndOfList {};

template <int Value>
struct Node<Value, EndOfList>
{
	static int const value = Value;
	
	static void print(std::ostream & os)
	{
		os << value << "\n";
	}
};

template <int Value, int NextVal, typename NextType>
struct Node<Value, Node<NextVal, NextType> >
{
	static int const value = Value;
	typedef Node<NextVal, NextType> next;
	
	static void print(std::ostream & os)
	{
		os << value << ", ";
		next::print(os);
	}
};

template <int Number, typename NumberList>
struct append;

template <int Number, int LastVal>
struct append<Number, Node<LastVal, EndOfList> >
{
	typedef Node<LastVal, Node<Number, EndOfList> > type;
};

template <int Number, int CurVal, int NextVal, typename NextNext>
struct append<Number, Node<CurVal, Node<NextVal, NextNext> > >
{
	typedef Node<CurVal, typename append<Number, Node<NextVal, NextNext> >::type> type;
};

int main()
{
	typedef Node<42, Node<23, Node<1337, EndOfList> > > number_list;
	number_list::print(std::cout);
	typedef typename append<1990, number_list>::type extended;
	extended::print(std::cout);
	return 0;
}
