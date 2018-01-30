// https://www.geeksforgeeks.org/system-call-in-c/
// A C++ program that pauses screen at the end in Windows OS
#include <iostream>
#include <string>

using namespace std;

int main ()
{
    string x = "echo \"Hello World\"";

    const char *command = x.c_str();
    
    cout << "Running program...\n";

    system(command);

    return 0;
}