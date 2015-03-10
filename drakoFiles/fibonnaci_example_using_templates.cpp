#include <iostream>
#include <array>

#ifndef MIN_INDEX
#define MIN_INDEX 0
#endif // MIN_INDEX

#ifndef MAX_INDEX
#define MAX_INDEX 15
#endif // MAX_INDEX

template <unsigned Index>
struct fib
{
    enum { value = fib<Index - 2>::value + fib<Index - 1>::value };
};

template <>
struct fib<0>
{
    enum { value = 1 };
};

template <>
struct fib<1>
{
    enum { value = 1 };
};

template <unsigned... Number>
struct sequence {};

template <unsigned Start, unsigned Count, bool CountNotZero = (Count != 0), typename Sequence = sequence<>>
struct generate_sequence;

template <unsigned Start, unsigned Count, unsigned... Numbers>
struct generate_sequence<Start, Count, true, sequence<Numbers...>>
{
    typedef typename generate_sequence<Start + 1, Count - 1, (Count - 1) != 0, sequence<Numbers..., Start>>::type type;
};

template <unsigned Start, typename Sequence>
struct generate_sequence<Start, 0, false, Sequence>
{
    typedef Sequence type;
};

template <typename Sequence>
struct array_filler;

template <unsigned... Indizes>
struct array_filler<sequence<Indizes...>>
{
    static std::array<unsigned, MAX_INDEX - MIN_INDEX + 1> const values;
};

template <unsigned... Indizes>
std::array<unsigned, MAX_INDEX - MIN_INDEX + 1> const array_filler<sequence<Indizes...>>::values = { fib<Indizes>::value... };

template <unsigned Begin, unsigned End>
std::array<unsigned, End - Begin + 1> const & fibonacci_numbers()
{
    return array_filler<typename generate_sequence<Begin, End - Begin + 1>::type>::values;
}

int main()
{
    for (auto n : fibonacci_numbers<MIN_INDEX, MAX_INDEX>())
        std::cout << n << std::endl;
    return 0;
}
