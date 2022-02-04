/*
    date: 2022-02-03 20:31

    this is a quick (and dirty) sandbox program to get an understanding of 
    the underlying architecture of c++. 

    before writing this program, I didn't understand the difference (in terms of bytes) between many of
    the data types I regularly use. for example, this allowed me to compare the 'char *' to the
    'std:string'.

    g++ -std=c++14 -o sizes cxxSizeExperiment.cxx
*/
#include <climits>
#include <cstdint>
#include <iostream>
#include <map>
#include <string>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>

using namespace std;

int gi = 42;

using put = pair<string,string>;

template<typename T>

using hMap = unordered_map<T,string>;

template<typename T1, typename T2>

using hMap2 = unordered_map<T1,T2>;

hMap<const char*> type1 = {
    {typeid(signed int).name(), "signed int"},
    {typeid(bool).name(), "bool"},
    {typeid(long long).name(), "long long"},
    {typeid(short).name(), "short"},
    {typeid(double).name(), "double"},
    {typeid(float).name(), "float"},
    {typeid(unsigned int).name(), "unsigned int"},
    {typeid(string).name(), "string"},
    {typeid(signed int *).name(), "signed int *"},
    {typeid(unsigned int *).name(), "unsigned int *"},
    {typeid(void *).name(), "void *"},
    {typeid(void).name(), "void"}
};

hMap<int> type2 = {
    {0, "signed int"},
    {1,"bool"},
    {2, "long long"},
    {3, "short"},
    {4, "double"},
    {5,"float"},
    {6, "unsigned int"},
    {7, "string"},
    {8, "signed int *"},
    {9, "unsigned int *"},
    {10, "void *"},
    {11, "void"}
};

hMap2<string, size_t> type3 = {
{"signed int", sizeof(signed int)},
{"bool", sizeof(bool)},
{"long long", sizeof(long long)},
{"short", sizeof(short)},
{"unsigned short", sizeof(unsigned short)},
{"double", sizeof(double)},
{"long double", sizeof(long double)},
{"float", sizeof(float)},
{"unsigned int", sizeof(unsigned int)},
{"unsigned long", sizeof(unsigned long)},
{"unsigned long long", sizeof(unsigned long long)},
{"string", sizeof(string)},
{"signed int *", sizeof(signed int *)},
{"unsigned int *", sizeof(unsigned int *)},
{"char *", sizeof(char *)},
{"nullptr", sizeof(nullptr)},
{"wchar_t", sizeof(wchar_t)},
{"char16_t", sizeof(char16_t)},
{"char32_t", sizeof(char32_t)},
{"intmax_t", sizeof(intmax_t)},
{"int8_t", sizeof(int8_t)},
{"int16_t", sizeof(int16_t)},
{"int32_t", sizeof(int32_t)},
{"int64_t", sizeof(int64_t)},
{"int_least8_t", sizeof(int_least8_t)},
{"int_least16_t", sizeof(int_least16_t)},
{"int_least32_t", sizeof(int_least32_t)},
{"int_least64_t", sizeof(int_least64_t)},
{"int_fast8_t", sizeof(int_fast8_t)},
{"int_fast16_t", sizeof(int_fast16_t)},
{"int_fast32_t", sizeof(int_fast32_t)},
{"int_fast64_t", sizeof(int_fast64_t)},
{"intptr_t", sizeof(intptr_t)},
{"uintmax_t", sizeof(uintmax_t)},
{"uint8_t", sizeof(uint8_t)},
{"uint16_t", sizeof(uint16_t)},
{"uint32_t", sizeof(uint32_t)},
{"uint64_t", sizeof(uint64_t)},
{"uint_least8_t", sizeof(uint_least8_t)},
{"uint_least16_t", sizeof(uint_least16_t)},
{"uint_least32_t", sizeof(uint_least32_t)},
{"uint_least64_t", sizeof(uint_least64_t)},
{"uint_fast8_t", sizeof(uint_fast8_t)},
{"uint_fast16_t", sizeof(uint_fast16_t)},
{"uint_fast32_t", sizeof(uint_fast32_t)},
{"uint_fast64_t", sizeof(uint_fast64_t)},
{"uintptr_t", sizeof(uintptr_t)}
};
 
/* using type2 */
template<typename T>
string getKey1(T param){
    auto key = type1.find(param);
    return key->second;
}

template<typename T>
string getKey2(T param){
    auto key = type2.find(param);
    return key->second;
}

struct test{
    int i;
    int *ip;
    bool b;
} test_obj[] = {
    [0] = {99, &gi, true}
};

int main() {
 
    cout << "Sizeof CHARBIT: " << CHAR_BIT << "\n";
    cout << "1: " << test_obj[0].i << "\n";
    cout << "type: " << getKey1(typeid(test_obj[0].i).name())
    // cout << "type: " << getKey2(0)
    << " | size (# of bits):" << (CHAR_BIT*sizeof(test_obj[0].i))<< "\nbits: ";     

    for(int n = (CHAR_BIT*sizeof(test_obj[0].i)); n--;){
        cout << static_cast<char>( ((test_obj[0].i & ( 1 << n)) != 0) + '0' );
    }

    cout << "\n2: " << test_obj[0].ip << "\n";
    cout << "type: " << getKey1(typeid(test_obj[0].ip).name())
    // cout << "type: " << getKey2(8)
        << " | size (# of bits):" << (CHAR_BIT*sizeof(test_obj[0].ip)) << "\n# of bits: ";

    for(int n = (CHAR_BIT*sizeof(test_obj[0].ip)); n--;){
    // cout << static_cast<char>( ((*test_obj[0].ip+n & ( 1 << n)) != 0) + '0' );
        cout << 'b';
    }

    cout << "\n3: " << test_obj[0].b << endl;
    // cout << "type: " << getKey2(1)
    cout << "type: " << getKey1(typeid(test_obj[0].b).name())
        << " | size (# of bits):" << (CHAR_BIT*sizeof(test_obj[0].b)) << "\nbits: ";

    for(int n = (CHAR_BIT*sizeof(test_obj[0].b)); n--;){
        cout << 'b';
    }

    cout << "\n";

    for(auto it= type3.begin(); it != type3.end(); it++){
        cout << "type: " << it->first
            << " | size (# of bytes): " << it->second
            << " | size (# of bits): " << (CHAR_BIT* it->second);
        cout << "\n";
    }

    return 0;
}
