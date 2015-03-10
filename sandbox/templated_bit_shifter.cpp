#include <iostream>

#include <cassert>
#include <climits>

// a nice class to access/modify single bits in an integer
template <typename BaseType = unsigned int>
class bitset
{
public:
	typedef BaseType base_type;
	
	// constructor, if no value is given, an appropriate 0 value is taken
	bitset(base_type value = base_type())
		: value_(value)
	{
	}
	
	// sets the [bit]th bit to 1
	void set(std::size_t bit)
	{
		assert(bit < (sizeof(base_type) * CHAR_BIT));
		
		value_ |= (1 << bit);
	}
	
	// sets the [bit]th bit to 0
	void unset(std::size_t bit)
	{
		assert(bit < (sizeof(base_type) * CHAR_BIT));
		
		value_ &= ~(1 << bit);
	}
	
	// check if the [bit]th bit is 1
	bool is_set(std::size_t bit)
	{
		assert(bit < (sizeof(base_type) * CHAR_BIT));
		
		return (value_ & (1 << bit)) != 0;
	}
	
	// used to print the value in binary
	std::ostream & print(std::ostream & os) const
	{
		for (int n = (sizeof(base_type) * CHAR_BIT); n--;)
			os << static_cast<char>(((value_ & (1 << n)) != 0) + '0');
		return os;
	}
	
	// left shift operator for demonstration
	bitset operator << (int offset)
	{
		return bitset(value_ << offset);
	}
	
	bitset & operator <<= (int offset)
	{
		value_ <<= offset;
		return *this;
	}

private:
	base_type value_;
};

// this allows as to write "cout << bs;" instead of "bs.print(cout)"
template <typename BaseType>
std::ostream & operator << (std::ostream & os, bitset<BaseType> const & bs)
{
	return bs.print(os);
}

int main()
{
	// some test code
	bitset<> bs(1337);
	std::cout << bs << "\n";
	bs.set(15);
	std::cout << bs << "\n";
	bs.unset(15);
	std::cout << bs << "\n";
	bs <<= 2;
	std::cout << bs << "\n";
	return 0;
}