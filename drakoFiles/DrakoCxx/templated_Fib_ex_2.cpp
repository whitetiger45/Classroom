#include <iostream>

template <unsigned N>
struct fib
{
  static unsigned const value = fib<N - 1>::value + fib<N - 2>::value;
};

template <>
struct fib<0>
{
  static unsigned const value = 1;
};

template <>
struct fib<1>
{
  static unsigned const value = 1;
};

template <unsigned... N>
struct sequence {};

template <unsigned S, unsigned E, typename SEQ = sequence<>>
struct gen_seq;
  
template <unsigned S, unsigned E, unsigned... N>
struct gen_seq<S, E, sequence<N...>>
{
  typedef typename gen_seq<S + 1, E, sequence<N..., S>>::type type;
};

template <unsigned E, unsigned... N>
struct gen_seq<E, E, sequence<N...>>
{
  typedef sequence<N..., E> type;
};

template <unsigned S, unsigned E, typename SEQ = typename gen_seq<S, E>::type>
struct fibonacci;
  
template <unsigned S, unsigned E, unsigned... N>
struct fibonacci<S, E, sequence<N...>>
{
  static unsigned const values[sizeof...(N)];
};

template <unsigned S, unsigned E, unsigned... N>
unsigned const fibonacci<S, E, sequence<N...>>::values[sizeof...(N)] = { fib<N>::value... };

int main()
{
  for (unsigned n : fibonacci<0, 20>::values)
    std::cout << n << std::endl;
  return 0;
}
