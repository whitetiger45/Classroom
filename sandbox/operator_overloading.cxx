#include <iostream>
using namespace std;

struct foo
{
    int m_bar;
    
    foo(int baz = 0)
    {
        m_bar = baz;
    }
    
    void setValue(int val)
    {
        m_bar = val;
    }
    
    void print(std::ostream & os)
    {
        os <<"\nValue of Bar: " <<  m_bar++ << "\n";
    }
    
    operator int () const
    {
        return m_bar;
    }
    
    std::ostream & operator <<(std::ostream & os)
    {
        os << m_bar;
        return os;
    }
    // friend std::ostream & operator <<(std::ostream & os, foo & f);
};

// std::ostream & operator <<(std::ostream & os, foo & f)
// {
//  os << f.m_bar;
    
//  return os;
// }

int main() 
{
    foo f;
    f.print(std::cout);
    f.setValue(10);
    f.print(std::cout);
    f.print(std::cout);
    cout << f;
    
    return 0;
}