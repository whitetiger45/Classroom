// https://www.geeksforgeeks.org/system-call-in-c/
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