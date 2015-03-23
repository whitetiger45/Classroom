#include <iostream>

#include <climits>
#include <cstddef>

using namespace std;

#define CHAR_MASK (~((~0) << CHAR_BIT))

#define DECLARE_CONVERSION \
	template <typename Type, size_t Size = sizeof(Type)> \
	struct conversion;
	
#define IMPLEMENT_CONVERSION(SIZE,FORMULA) \
	template <typename Type> \
	struct conversion<Type, SIZE> \
	{ \
		static inline Type apply(unsigned char (&c)[SIZE]) \
		{ \
			return FORMULA; \
		} \
	};

struct BigEndian
{
	DECLARE_CONVERSION
	IMPLEMENT_CONVERSION(1, (c[0]))
	IMPLEMENT_CONVERSION(2, ((c[0] << CHAR_BIT) | c[1]))
	IMPLEMENT_CONVERSION(4, ((c[0] << (CHAR_BIT * 3)) | (c[1] << (CHAR_BIT * 2)) | (c[2] << CHAR_BIT) | c[3]))
	
	template <typename Type>
	static inline Type convert(Type val)
	{
		union
		{
			Type v;
			unsigned char b[sizeof(Type)];
		} splitter = { .v = val };
		return conversion<Type>::apply(splitter.b);
	}
};

struct LittleEndian
{
	DECLARE_CONVERSION
	IMPLEMENT_CONVERSION(1, (c[0]))
	IMPLEMENT_CONVERSION(2, ((c[1] << CHAR_BIT) | c[0]))
	IMPLEMENT_CONVERSION(4, ((c[3] << (CHAR_BIT * 3)) | (c[2] << (CHAR_BIT * 2)) | (c[1] << CHAR_BIT) | c[0]))
	
	template <typename Type>
	static inline Type convert(Type val)
	{
		union
		{
			Type v;
			unsigned char b[sizeof(Type)];
		} splitter = { .v = val };
		return conversion<Type>::apply(splitter.b);
	}
};

template <typename BaseType, typename EndianPolicy>
class endian_int
{
public:
	typedef EndianPolicy endianess;
	typedef BaseType base_type;
	
	endian_int(base_type value = 0)
		: value_(endianess::convert(value))
	{
	}
	
	endian_int(endian_int const & src)
		: value_(src.value_)
	{
	}
	
	endian_int & operator = (endian_int const & src)
	{
		value_ = src.value_;
		return *value_;
	}
	
	operator base_type() const
	{
		return endianess::convert(value_);
	}
	
	base_type raw() const
	{
		return value_;
	}
	
private:
	base_type value_;
};

template <typename BaseType, typename EndianPolicy>
ostream & operator << (ostream & os, endian_int<BaseType, EndianPolicy> const & val)
{
	return os << val.operator BaseType();
}

template <typename BaseType, typename EndianPolicy>
istream & operator >> (istream & is, endian_int<BaseType, EndianPolicy> & val)
{
	BaseType tmp;
	is >> tmp;
	val = endian_int<BaseType, EndianPolicy>(tmp);
	return is;
}

typedef endian_int<unsigned char, BigEndian>    be_uint8_t;
typedef endian_int<signed char  , BigEndian>    be_int8_t;
typedef endian_int<unsigned char, LittleEndian> le_uint8_t;
typedef endian_int<signed char  , LittleEndian> le_int8_t;

typedef endian_int<unsigned short, BigEndian>    be_uint16_t;
typedef endian_int<short         , BigEndian>    be_int16_t;
typedef endian_int<unsigned short, LittleEndian> le_uint16_t;
typedef endian_int<short         , LittleEndian> le_int16_t;

typedef endian_int<unsigned int, BigEndian>    be_uint32_t;
typedef endian_int<int         , BigEndian>    be_int32_t;
typedef endian_int<unsigned int, LittleEndian> le_uint32_t;
typedef endian_int<int         , LittleEndian> le_int32_t;

int main()
{
	be_int32_t be_answer(42);
	le_int32_t le_answer(42);
	
	cout << be_answer << " -> " << be_answer.raw() << endl;
	cout << le_answer << " -> " << le_answer.raw() << endl;
	
	return 0;
}