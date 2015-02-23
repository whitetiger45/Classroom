#include <algorithm>
#include <array>
#include <complex>
#include <iostream>
#include <iterator>

#include <cmath>

namespace detail
{
    using namespace std;

    template <typename T>
    struct pi;

    template <> struct pi <float> { static float const value; };
    float const pi<float>::value = 3.14159265358979323846f;

    template <> struct pi <double> { static double const value; };
    double const pi<double>::value = 3.14159265358979323846;

    template <> struct pi <long double> { static long double const value; };
    long double const pi<long double>::value = 3.14159265358979323846L;
    
    template <typename ValueType, size_t Size, size_t j = Size>
    struct adder
    {
        ValueType apply(size_t k, array<complex<ValueType>, Size> const & buffer)
        {
            return
                exp(
                    -2.0 *
                    pi<ValueType>::value *
                    complex<ValueType>(0.0, 1.0) *
                    static_cast<ValueType>(j - 1) *
                    static_cast<ValueType>(k) /
                    static_cast<ValueType>(Size))
                * buffer[j - 1]
                + adder<ValueType, Size, j - 1>::apply(k, buffer);
        }
    };
    
    template <typename ValueType, size_t Size>
    struct adder<ValueType, Size, 0>
    {
        ValueType apply(size_t, array<complex<ValueType>, Size> const &)
        {
            return ValueType();
        }
    };

    template <typename ValueType, size_t Size>
    struct dft
    {
        static void apply(array<complex<ValueType>, Size> & buffer)
        {
            for (size_t k = 0; k < Size; ++k)
            {
                buffer[k] = adder<ValueType, Size>::apply(k, buffer);
            }
        }
    };

    template <typename ValueType>
    struct dft <ValueType, 1>
    {
        static void apply(array<complex<ValueType>, 1> &)
        {
            // do nothing
        }
    };

    template <typename ValueType, size_t Size, bool Odd = Size % 2>
    struct fft
    {
        static void apply(array<complex<ValueType>, Size> & buffer)
        {
            array<array<complex<ValueType>, Size / 2>, 2> halfs;
            complex<ValueType> i(0.0, 1.0);

            for (size_t sample = Size; sample--;)
                halfs[sample % 2][sample / 2] = buffer[sample];
            fft<ValueType, Size / 2>::apply(halfs[0]);
            fft<ValueType, Size / 2>::apply(halfs[1]);

            complex<ValueType> freqfac = -pi<ValueType>::value * i * 2.0 / static_cast<ValueType>(Size);

            size_t k = 0;
            for (; k < (Size / 2); ++k)
                buffer[k] = halfs[0][k] + exp(freqfac * static_cast<ValueType>(k)) * halfs[1][k];
            for (; k < Size; ++k)
                buffer[k] = halfs[0][k - (Size / 2)] - exp(freqfac * static_cast<ValueType>(k - (Size / 2))) * halfs[1][k - (Size / 2)];
        }
    };

    template <typename ValueType, size_t Size>
    struct fft<ValueType, Size, true>
        : public dft <ValueType, Size>
    {
    };
}

// actually only Size / 2 elements are used for the results
// the second half are more or less garbage values
template <typename ValueType, std::size_t Size>
void fft(std::array<ValueType, Size> & buffer)
{
    std::array<std::complex<ValueType>, Size> tmp;
    std::transform(std::begin(buffer), std::end(buffer), std::begin(tmp), [](ValueType val){
        return std::complex<ValueType>(val, 0.0);
    });
    detail::fft<ValueType, Size>::apply(tmp);
    std::transform(std::begin(tmp), std::end(tmp), std::begin(buffer), [](std::complex<ValueType> val){
        return std::abs(val) / static_cast<ValueType>(Size / 2);
    });
}

template <typename ValueType, std::size_t Size>
void fft(std::array<std::complex<ValueType>, Size> & buffer)
{
    detail::fft<ValueType, Size>::apply(buffer);
}

int main()
{
    std::array<double, 8192> source_signal;
    unsigned n = 0;

    std::generate(std::begin(source_signal), std::end(source_signal), [n]() mutable {
        double t = n++ * 1.0 / 8192;
        return 200.0 * std::sin(detail::pi<double>::value * 2.0 * 10.0 * t);
    });

    fft(source_signal);

    std::cout << source_signal[10] << std::endl;

    return 0;
}
