#include <iostream>
#include <string>
 
using namespace std;
 
int main() 
{
    string _python = "( ! ( test -e tmp.py ) ) && ( ( echo \"#! /bin/bash\\n\\n"
    "a=\\\"hello world from python\\\"\\n\\nprint(\\\"{0}\\\".format(a))\\n\\n\" > tmp.py ) "
    "&& ( python tmp.py ) ) || ( python tmp.py ) ";
 
    string _shell1 = "( ! ( test -e tmp.sh ) ) && ( ( echo \"!#/bin/bash\\n\\n"
    "a=\\\"hello world from bash\\\"\\n\\necho \\\"$a\\\"\\n\\n\" > tmp.sh ) "
    "&& ( ( chmod u+x tmp.sh ) && ( ./tmp.sh) ) ) || ( ./tmp.sh ) ";
 
    string _shell2 = "( ! ( test -e tmp.sh ) ) && ( ( echo \"!#/bin/bash\\n\\n"
    "a=\\\"hello world from bash\\\"\\n\\necho \\\"$a\\\"\\n\\n\" > tmp.sh ) "
    "&& ( bash tmp.sh ) ) || ( bash tmp.sh ) ";
 
    const char * command = _python.c_str();
    cout << "1) " << _python << "\n\n2) " << _shell1 << "\n\n3) " << _shell2 << "\n";
 
    system(command);
    return 0;
}