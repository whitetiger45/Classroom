#include <iostream>
#include <string>
 
using namespace std;
 
int main() 
{
    string _program = "( ! ( test -e tmp.py ) ) && ( ( echo \"#! /bin/bash\\n\\n"
    "a=\\\"hello world from python\\\"\\n\\nprint(\\\"{0}\\\".format(a))\\n\\n\" > tmp.py ) "
    "&& ( python tmp.py ) ) || ( python tmp.py )";
 
    const char * command = _program.c_str();
    cout << _program << endl;
 
    system(command);
    return 0;
}