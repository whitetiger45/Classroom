#include <iostream>

template <int Width>
struct __distance;

template <int Width, int Height, bool Increment = true>
struct __area
{
	__area<Width, Height + Increment, !Increment> operator ! () const
	{
		return __area<Width, Height + Increment, !Increment>();
	}
	
	__area<Width, Height, Increment> operator - (__distance<0> const &)
	{
		return __area<Width, Height, Increment>();
	}
};

template <int Width, int Height, bool Increment>
std::ostream & operator << (std::ostream & os, __area<Width, Height, Increment> const &)
{
	return os << Width << "m x " << Height << "m";
}

template <int Width>
struct __distance
{
	__distance<Width + 1> operator -- (int)                   const { return __distance<Width + 1>(); }
	__distance<Width>     operator -  (__distance<0> const &)       { return __distance<Width>();     }
	__area<Width, 1>      operator !  ()                      const { return __area<Width, 1>();      }
	
	template <int AHeight, bool AInc>
	__area<Width, AHeight + 1> operator | (__area<Width, AHeight, AInc> const &) const
	{
		return __area<Width, AHeight + 1>();
	}
};

static __distance<0> const I;

template <int Width>
std::ostream & operator << (std::ostream & os, __distance<Width> const &)
{
	return os << Width << "m";
}

int main()
{
	std::cout << I---------I << std::endl;
	std::cout << (I-------------I
				  |             !
				  !             !
				  !             !
				  !             !
				  !             !
				  !             !
				  I-------------I) << std::endl;
	return 0;
}