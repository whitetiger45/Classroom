#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

class DataType
{
public:
    enum Type { BIT, BLOCK, BYTE, DWORD, FLOAT, INTEGER, WORD, SHORT, STRING, UBYTE, DATE, TIME, SINT32 };
    
    DataType()
        : m_value(BIT)
    {
    }
    
    DataType(Type t/* = BIT*/)// could also uncomment the = BIT portion and comment out the first constructor
        : m_value(t)
    {
    }
    
    DataType(DataType const & src)
        : m_value(src.m_value)
    {
    }
    
    DataType & operator = (DataType const & src)
    {
        m_value = src.m_value;
        return *this;
    }
    
    operator Type () const
    {
        return m_value;
    }
    
    std::string toDisplayString() const
    {
        return m_typeStrings[m_value];
    }
    
    static std::vector<DataType> getNativeSPSTypes()
    {
        return std::vector<DataType>(m_nativeTypes, m_nativeTypes +  7);
    }
    
private:
    static const Type m_nativeTypes[7];
    static const std::string m_typeStrings[13];
    
    Type m_value;
};

const DataType::Type DataType::m_nativeTypes[7] = {
    DWORD,WORD,UBYTE,BLOCK,BIT,FLOAT,SINT32
};

const std::string DataType::m_typeStrings[13] = {
    "bit", "bytes", "sbyte", "dword", "float",
    "integer", "word", "short", "string", "byte",
    "date", "time", "signed int32"
};

std::ostream & operator << (std::ostream & os, DataType const & dt)
{
    return os << dt.toDisplayString();
}

int main()
{
//  DataType dt = DataType::SINT32;
//  std::cout << dt << std::endl;
    std::vector<DataType> nativeTypes = DataType::getNativeSPSTypes();
    std::copy(nativeTypes.begin(), nativeTypes.end(), std::ostream_iterator<DataType>(std::cout, "\n"));

    return 0;
}
