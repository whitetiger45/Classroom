#include <iostream>
#include <string>

#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"

using namespace cgicc;
using namespace std;
// python -m CGIHTTPServer
int main(int argc, char **argv)
{
    Cgicc formdata;
    form_iterator fi;
    string name = "";
    fi = formdata.getElement("uname");

    if(fi != (*formdata).end())
    {
        name = **fi;
    }

    cout<< cgicc::HTTPHTMLHeader();
    //set up the html document
    cout << "<html>\n<head>\n<title>Hello World</title>\n</head>\n<body style=\"text-align:center;\">\n";
    cout << "<form method=\"POST\">\n";
    cout << "Name: <input type=\"text\" name=\"uname\" style=\"text-align: center;\" value=\"" << name << "\">\n<br>\n";
    cout << "<input type=\"submit\" value=\"submit\" style=\"margin-left: 303px;\">";
    cout << "</form>\n";
    cout << "<p id=\"result\">Hello " << name << "!</p>\n</body>\n</html>";

    return 0;
}