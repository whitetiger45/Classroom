// vector::data
#include <iostream>
#include <vector>

int main ()
{
  std::vector<int> myvector (5);
  std::vector<int, std::allocator<int> > m_vector(5, 9);//initialize with size 5
  //std::vector<int, std::allocator<int> > m_vector(5, 23); //this also works, initialize it with size 5, all 23s
  //m_vector[5];
  int* p = myvector.data();

  *p = 10;
  ++p;
  *p = 20;
  p[2] = 100;
  //m_vector.push_back(*p);
  std::vector<int, std::allocator<int> > * q;
  q = &m_vector;
  int x = (*q)[3];
  //int z = q[2];
    //q++;
  //q[2] = 30;
  std::cout << "myvector contains:";
  for (unsigned i=0; i<m_vector.size(); ++i)
  {
    std::cout << ' ' << m_vector[i];
  }
  std::cout << '\n';
  std::cout << "x: " <<  x <<  '\n';

  return 0;
}