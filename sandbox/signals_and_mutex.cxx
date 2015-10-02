// thread example
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <iostream>
#include <stdio.h>      /* printf */
#include <signal.h>     /* signal, raise, sig_atomic_t */
#include <string>
#include <mutex>

sig_atomic_t signaled = 0;
std::string fooo;
int count = 0;
void s_handler (std::string param)
{
  std::cout << "Welcome to Siemens PLM Milford\n";
}

std::string m_handler (int param)
{
    std::string ret;
    if(param)
      std::cout << "variable set\n";
  
    ret = "Hello World";
    s_handler(ret);
    return ret;
}

void m_handler()
{
    std::cout << "This is executed in the first thread\n";
}

void my_handler (int param)
{
  signaled = 1;
  fooo = m_handler(signaled);
}

std::mutex mtx;           // mutex for critical section

int x = 0;

void foo() 
{
  m_handler();
  ::count++;
  std::cout<<"count: " << ::count << "\n";
}

void bar(int a)
{
  raise(SIGINT);
    ::count++;
    std::cout<<"count: " << ::count << "\n";
    mtx.lock();
    ::x++;
    std::cout<<"x inside bar: " << ::x << "\n";
    mtx.unlock();
}

void baz()
{
    mtx.lock();
    ::x = 9;
    std::cout<<"x inside baz: " << ::x << "\n";
    mtx.unlock();
    ::count++;
    std::cout<<"count: " << ::count << "\n";
}

int main() 
{
  void (*prev_handler)(int);
  void (*p_handler)(int);
  void (*s_handler)(std::string);
  
  prev_handler = signal (SIGINT, my_handler);

  std::thread third (baz);
  std::thread first (foo);     // spawn new thread that calls foo()
  std::thread second (bar, x);  // spawn new thread that calls bar(0)


  std::cout << "main, foo and bar & baz now execute concurrently...\n";

  // synchronize threads:
  first.join();                // pauses until first finishes
  second.join();               // pauses until second finishes
  third.join();
  std::cout << "x after joining threads: " << x << "\n";
  std::cout << "Foo: " << fooo << "\n";

  return 0;
}